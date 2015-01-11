
#include "app/window.h"

OC_NS_BG;

namespace
{
    LRESULT CALLBACK windowProcImpl( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
    {
        LONG_PTR func = GetWindowLongPtr(hwnd, 0);

        if (func == 0) 
        {
            return( DefWindowProc(hwnd, msg, wparam, lparam) );
        } 
        else 
        {
            Window::WndProc* wndProc = (Window::WndProc*)func;
            return( (*wndProc)(hwnd, msg, wparam, lparam) );
        }
    }
}

Window::Window(const String& caption)
    : m_hWnd(NULL)
    , m_caption(caption)
    , m_width(1024)
    , m_height(768)
    , m_left(200)
    , m_top(150)
    , m_style(WS_OVERLAPPEDWINDOW)
{
}

Window::~Window()
{
    shutdown();
}

bool Window::initialize(WndProc wndProc)
{
    m_wndProc = wndProc;

    WNDCLASS wc;
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = windowProcImpl; 
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = sizeof(m_wndProc);
    wc.hInstance     = 0;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "OCWndClassName"; // Name of the class (for registration)

    // Registers a window class for subsequent use in calls to the CreateWindow or CreateWindowEx function
    if( !RegisterClass(&wc) )
    {
        MessageBox(0, "RegisterClass Failed.", 0, 0);
        return false;
    }

    RECT R = { 0, 0, m_width, m_height };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
    int width  = R.right - R.left;
    int height = R.bottom - R.top;

    // Adjust the window size for correct device size
    AdjustWindowRect(&R, m_style, FALSE);

    // Create an instance of the window
    m_hWnd = CreateWindowEx(
        NULL,							// extended style
        wc.lpszClassName, 			
        m_caption.c_str(),
        m_style,                        // window style
        CW_USEDEFAULT, CW_USEDEFAULT,   // initial x, y
        width,							// initial width
        height,                         // initial height
        NULL,	                        // handle to parent 
        NULL,                           // handle to menu
        NULL,                           // instance of this application
        NULL );                         // extra creation params

    if(!m_hWnd)
    {
        MessageBox(0, "CreateWindow Failed.", 0, 0);
        return false;
    }

    // Set in the "extra" bytes the pointer to the IWindowProc object
    // which handles messages for the window
    SetWindowLongPtr(m_hWnd, 0, (LONG_PTR)&m_wndProc);

    // Initially display the window
    ShowWindow(m_hWnd, SW_SHOWNORMAL);

    // The UpdateWindow function updates the client area of the specified window by sending a 
    // WM_PAINT message to the window if the window's update region is not empty. 
    UpdateWindow(m_hWnd);

    return true;
}

void Window::shutdown()
{
    if (m_hWnd)
        DestroyWindow(m_hWnd);

    m_hWnd = 0;
}

HWND Window::getHandle()
{
    return m_hWnd;
}

void Window::setWidth(uint32 width)
{
    m_width = width;
}

void Window::setHeight(uint32 height)
{
    m_height = height;
}

int Window::getWidth()
{
    return m_width;
}

int Window::getHeight()
{
    return m_height;
}

int Window::getLeft()
{
    return m_left;
}

int Window::getTop()
{
    return m_top;
}

void Window::setSize(uint32 width, uint32 height)
{
    m_width = width;
    m_height = height;
    updateWindow();
}

void Window::setPosition(uint32 left, uint32 top)
{
    m_left = left;
    m_top = top;
    updateWindow();
}

void Window::resize(int width, int height)
{
    m_width = width;
    m_height = height;
    updateWindow();
}

void Window::setCaption(const String& caption)
{
    m_caption = caption;
    SetWindowText(m_hWnd, caption.c_str());
}

void Window::setStyle(DWORD dStyle)
{
    m_style = dStyle;
    updateWindow();
}

void Window::updateWindow()
{
    OC_ASSERT(m_hWnd != NULL);

    RECT clientRect;
    clientRect.left = 0;
    clientRect.top = 0;
    clientRect.right = m_width;
    clientRect.bottom = m_height;

    // Adjust the window size for correct device size
    RECT windowRect = clientRect;
    AdjustWindowRect(&windowRect, m_style, FALSE);

    int deltaX = (windowRect.right - clientRect.right) / 2;
    int deltaY = (windowRect.bottom - clientRect.bottom) / 2;

    MoveWindow(m_hWnd, m_left - deltaX, m_top - deltaY, 
        m_width + deltaX * 2, m_height + deltaY * 2, true);
}

OC_NS_END;