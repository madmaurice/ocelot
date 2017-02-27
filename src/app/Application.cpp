#include "app/Application.h"
#include "graphic/Graphic.h"
#include <functional>

OC_NS_BG;


namespace 
{
    const static float s_targetFrameRateMs = (float)(1.0f / 60.0f) * 1000.0f;
    const bool s_fullScreen = false;
    const bool s_enableVSync = false;
    const bool s_selectBestMSAAQuality = false;

    class FpsCounter
    {
    public:
        FpsCounter::FpsCounter()
            : m_fps(0)
            , m_frameCount(0)
            , m_elapsedTime(0)
        { }

        // Need to be called on every frames
        void FpsCounter::UpdateFrame(float runningTimeMs)
        {
            ++m_frameCount;
            m_elapsedTime += runningTimeMs;

            // Compute average over 1 seconds period
            if (m_elapsedTime >= 1000.0f)
            {
                // Reset frame count for next average
                m_fps = m_frameCount;

                m_frameCount = 0;
                m_elapsedTime = 0.0f;
            }
        }

        uint32 GetFps() const { return m_fps; }
        float GetFrameTimeMs() const { return m_fps > 0 ? 1000 / (float)m_fps : 0; }

    private:
        uint32 m_fps;
        uint32 m_frameCount;
        float m_elapsedTime;
    };
    static FpsCounter s_fpsCounter;

    void UpdateWindowCaption(Window& window, const String& appName, uint32 fps, float frameTime)
    {
        std::ostringstream outs;   
        outs << appName << "    "
            << "FPS: " << fps << "    " 
            << "Frame Time: " << frameTime * 1000 << " (ms)";
        window.SetCaption(outs.str());
    }
}

Application::Application(const String& name)
    : m_window(name)
    , m_name(name)
    , m_paused(false)
    , m_resizing(false)
    , m_minimized(false)
    , m_maximized(false)
    , m_shutdown(false)
    , m_initCompleted(false)
{
}

Application::~Application()
{
    OC_ASSERT(m_shutdown == true);
}

bool Application::Initialize()
{
    LoggingConfig logConfig;
    logConfig.AddAppender(std::make_unique<DebugConsoleAppender>());
    logConfig.SetLogLevel(LogLevel::Debug);
    return Initialize(logConfig);
}

bool Application::Initialize(const LoggingConfig& config)
{
    using namespace std::placeholders;

    Logger::Init(config);

    OC_LOG_INFO("Logging configured");

    Window::WndProc wndProc = std::bind(&Application::WndProc, this, _1, _2, _3, _4);
    if (!m_window.Initialize(wndProc))
    {
        OC_LOG_ERROR("Application initialization failed : Window init failed!");
        return false;
    }

    GraphicConfig graphicConfig = { m_window.GetWidth(), m_window.GetHeight(), 1, 0, s_fullScreen, s_enableVSync, s_selectBestMSAAQuality };
    if (!Graphic::Initialize(m_window.GetHandle(), graphicConfig))
    {
        OC_LOG_ERROR("Application initialization failed : Graphic init failed!");
        return false;
    }

    if (!InitializeImpl())
    {
        OC_LOG_ERROR(m_name + " initialization failed");
        return false;
    }

    m_initCompleted = true;
    return true;
}

void Application::Shutdown()
{
    OC_LOG_INFO(m_name + " is shutting down");

    if (!m_shutdown)
    {
        ShutdownImpl();
        Graphic::Shutdown();
        m_window.Shutdown();

        m_shutdown = true;
    }
}

void Application::Run()
{
    m_timer.Reset();

    MSG msg  = {0};


    bool running = true;
    float currentFrameTimeMs = s_targetFrameRateMs;
    while(running)
    {
        while (PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ))
        { 
            if (msg.message == WM_QUIT)
            {
                running = false;
                Shutdown();
                return;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        m_timer.Tick();
        currentFrameTimeMs += m_timer.GetDeltaMs();
        const bool runFrame = !m_paused && (s_enableVSync || currentFrameTimeMs >= s_targetFrameRateMs);
        if (runFrame)
        {
            s_fpsCounter.UpdateFrame(currentFrameTimeMs);

            // Call the overloaded application update and render functions.
            Update(currentFrameTimeMs / 1000);
            Render();

            currentFrameTimeMs = 0;
        }
        else
        {
            const int sleepTime = (int)(s_targetFrameRateMs - currentFrameTimeMs);
            if (sleepTime > 1)
            {
                Sleep(sleepTime);
            }
        }
    }
}

void Application::Update(float elapsed)
{
    // Update FPS on window title
    UpdateWindowCaption(m_window, m_name, s_fpsCounter.GetFps(), elapsed);

    UpdateImpl(elapsed);
}

void Application::Render()
{
    Graphic::Clear();

    RenderImpl();

    // TODO : render debug HUD
    Graphic::Present();
}

void Application::Pause()
{
    if (!IsDebuggerPresent() && !m_paused)
    {
        m_timer.Stop();
        m_paused = true;
    }
}

void Application::Unpause()
{
    if (!IsDebuggerPresent() && m_paused)
    {
        m_timer.Start();
        m_paused = false;
    }
}

void Application::OnResize(uint32 width, uint32 height)
{
    OC_LOG_DEBUG("Application::onResize : width=" << width << ", height=" << height);
    Graphic::Resize(width, height);
}

LRESULT Application::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static uint16 windowWidth  = static_cast<uint16>(m_window.GetWidth());
    static uint16 windowHeight = static_cast<uint16>(m_window.GetHeight());

    switch(msg)
    {
        // WM_ACTIVATE is sent when the window is activated or deactivated.  
        // We pause the app when the window is deactivated and unpause it 
        // when it becomes active.  
    case WM_ACTIVATE:
        if( LOWORD(wParam) == WA_INACTIVE )
        {
            Pause();
        }
        else
        {
            Unpause();
        }
        return 0;

        // WM_SIZE is sent when the user resizes the window.  
    case WM_SIZE:
        {
            // Need to wait Direct3D to be initialized before performing any resizing.
            if (!m_initCompleted)
            {
                return 0;
            }

            // Save the new client area dimensions.
            windowWidth  = LOWORD(lParam);
            windowHeight = HIWORD(lParam);
            if(wParam == SIZE_MINIMIZED)
            {
                Pause();
                m_minimized = true;
                m_maximized = false;
            }
            else if(wParam == SIZE_MAXIMIZED)
            {
                Unpause();
                m_minimized = false;
                m_maximized = true;
                OnResize(windowWidth, windowHeight);
            }
            else if(wParam == SIZE_RESTORED)
            {
                // Restoring from minimized state?
                if( m_minimized )
                {
                    Unpause();
                    m_minimized = false;
                    OnResize(windowWidth, windowHeight);
                }
                // Restoring from maximized state?
                else if(m_maximized)
                {
                    Unpause();
                    m_maximized = false;
                    OnResize(windowWidth, windowHeight);
                }
                else if(m_resizing)
                {
                    // If user is dragging the resize bars, we do not resize 
                    // the buffers here because as the user continuously 
                    // drags the resize bars, a stream of WM_SIZE messages are
                    // sent to the window, and it would be pointless (and slow)
                    // to resize for each WM_SIZE message received from dragging
                    // the resize bars.  So instead, we reset after the user is 
                    // done resizing the window and releases the resize bars, which 
                    // sends a WM_EXITSIZEMOVE message.
                }
                else // API call such as SetWindowPos or SwapChain->SetFullscreenState.
                {
                    OnResize(windowWidth, windowHeight);
                }
            }
            return 0;
        }

        // WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
    case WM_ENTERSIZEMOVE:
        Pause();
        m_resizing  = true;
        m_timer.Stop();
        return 0;

        // WM_EXITSIZEMOVE is sent when the user releases the resize bars.
        // Here we reset everything based on the new window dimensions.
    case WM_EXITSIZEMOVE:
        Unpause();
        m_resizing  = false;
        m_timer.Start();
        OnResize(windowWidth, windowHeight);
        return 0;

        // WM_DESTROY is sent when the window is being destroyed.
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

        // The WM_MENUCHAR message is sent when a menu is active and the user presses 
        // a key that does not correspond to any mnemonic or accelerator key. 
    case WM_MENUCHAR:
        // Don't beep when we alt-enter.
        return MAKELRESULT(0, MNC_CLOSE);

        // Catch this message so to prevent the window from becoming too small.
    case WM_GETMINMAXINFO:
        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200; 
        return 0;

    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
        // TODO
        //OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
        // TODO
        //OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;
    case WM_MOUSEMOVE:
        // TODO
        //OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

OC_NS_END;