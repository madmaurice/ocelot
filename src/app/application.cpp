#include "app/application.h"
#include <functional>

OC_NS_BG;

namespace 
{
    void updateWindowCaption(Window& window, const String& appName, const FpsCounter& fps)
    {
        std::ostringstream outs;   
        outs << appName << "    "
            << "FPS: " << fps.getFps() << "    " 
            << "Frame Time: " << fps.getFrameTimeMs() << " (ms)";
        window.setCaption(outs.str());
    }
}

Application::Application(const String& name)
    : m_paused(false)
    , m_resizing(false)
    , m_minimized(false)
    , m_maximized(false)
    , m_shutdown(false)
    , m_window(name)
    , m_name(name)
{
}

Application::~Application()
{
    OC_ASSERT(m_shutdown == true);
}

bool Application::initialize()
{
    LoggingConfig logConfig;
    logConfig.addAppender(make_unique<DebugConsoleAppender>());
    return initialize(logConfig);
}

bool Application::initialize(const LoggingConfig& config)
{
    using namespace std::placeholders;

    Logger::init(config);

    OC_LOG_INFO("Logging configured");

    Window::WndProc wndProc = std::bind(&Application::wndProc, this, _1, _2, _3, _4);
    if (!m_window.initialize(wndProc))
    {
        OC_LOG_ERROR("Window initialization failed");
        return false;
    }

    // TODO : initialize other systems (DX3D)

    if (!initializeImpl())
    {
        OC_LOG_ERROR(m_name + " initialization failed");
        return false;
    }

    return true;
}

void Application::shutdown()
{
    OC_LOG_INFO(m_name + " is shutting down");

    if (!m_shutdown)
    {
        shutdownImpl();
        m_window.shutdown();

        m_shutdown = true;
    }
}

void Application::run()
{
    // Call update (limit FPS?)
    m_timer.reset();

    MSG msg  = {0};

    bool running = true;
    while(running)
    {
        while (PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ))
        { 
            if (msg.message == WM_QUIT)
            {
                running = false;
                return;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        m_timer.tick();

        if (!m_paused)
        {
            // Call the overloaded application update function.
            update();

            // TODO : better frame rate limit...
            Sleep(15);
        }
        else
        {
            Sleep(100);
        }
    }
}

void Application::update()
{
    // TODO
    // processMessage (dispatch?), update engine
    m_fpsCounter.updateFrame(m_timer.getElapsed());

    // Update FPS on window title
    updateWindowCaption(m_window, m_name, m_fpsCounter);

    updateImpl(m_timer.getDelta());
}

void Application::handleResize(uint32 width, uint32 height)
{
    OC_UNUSED(width);
    OC_UNUSED(height);

    // TODO : Render system resize
    OC_LOG_ALWAYS("Resize : width=" << width << ", height=" << height);
}

LRESULT Application::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static uint16 windowWidth  = static_cast<uint16>(m_window.getWidth());
    static uint16 windowHeight = static_cast<uint16>(m_window.getHeight());

    switch(msg)
    {
        // WM_ACTIVATE is sent when the window is activated or deactivated.  
        // We pause the app when the window is deactivated and unpause it 
        // when it becomes active.  
    case WM_ACTIVATE:
        if( LOWORD(wParam) == WA_INACTIVE )
        {
            m_paused = true;
            m_timer.stop();
        }
        else
        {
            m_paused = false;
            m_timer.start();
        }
        return 0;

        // WM_SIZE is sent when the user resizes the window.  
    case WM_SIZE:
        {
            // Save the new client area dimensions.
            windowWidth  = LOWORD(lParam);
            windowHeight = HIWORD(lParam);
            if(wParam == SIZE_MINIMIZED)
            {
                m_paused = true;
                m_minimized = true;
                m_maximized = false;
            }
            else if(wParam == SIZE_MAXIMIZED)
            {
                m_paused = false;
                m_minimized = false;
                m_maximized = true;
                handleResize(windowWidth, windowHeight);
            }
            else if(wParam == SIZE_RESTORED)
            {
                // Restoring from minimized state?
                if( m_minimized )
                {
                    m_paused = false;
                    m_minimized = false;
                    handleResize(windowWidth, windowHeight);
                }
                // Restoring from maximized state?
                else if(m_maximized)
                {
                    m_paused = false;
                    m_maximized = false;
                    handleResize(windowWidth, windowHeight);
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
                    handleResize(windowWidth, windowHeight);
                }
            }
            return 0;
        }

        // WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
    case WM_ENTERSIZEMOVE:
        m_paused = true;
        m_resizing  = true;
        m_timer.stop();
        return 0;

        // WM_EXITSIZEMOVE is sent when the user releases the resize bars.
        // Here we reset everything based on the new window dimensions.
    case WM_EXITSIZEMOVE:
        m_paused = false;
        m_resizing  = false;
        m_timer.start();
        handleResize(windowWidth, windowHeight);
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