
#pragma once

#include "core/util/NonCopyable.h"
#include <windows.h>
#include <functional>


OC_NS_BG;

class Window : public NonCopyable
{
public:
    typedef std::function<LRESULT(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)> WndProc;

    explicit Window(const String& caption = "OCWindow");
    ~Window();

    bool Initialize(WndProc wndProc);
    void Shutdown();

    HWND GetHandle();

    void SetWidth(uint32 width);
    void SetHeight(uint32 height);

    int GetWidth();
    int GetHeight();

    int GetLeft();
    int GetTop();

    void SetSize(uint32 width, uint32 height);
    void SetPosition(uint32 left, uint32 top);

    void Resize(int width, int height);

    void SetCaption(const String& caption);
    void SetStyle(DWORD dStyle);

protected:

    void UpdateWindow();

    HWND    m_hWnd;
    String	m_caption;
    uint32	m_width;
    uint32 	m_height;
    uint32 	m_left;
    uint32  m_top;

    DWORD	m_style;
    WndProc m_wndProc;
};

OC_NS_END;