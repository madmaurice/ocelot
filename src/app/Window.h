
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

    HWND GetHandle() const { return m_hWnd; }

    void SetWidth(uint32 width);
    void SetHeight(uint32 height);

    uint32 GetWidth() const { return m_width; }
    uint32 GetHeight() const { return m_height; }

    uint32 GetLeft() const { return m_left; }
    uint32 GetTop() const { return m_top; }

    void SetPosition(uint32 left, uint32 top);
    void Resize(uint32 width, uint32 height);

    void SetCaption(const String& caption);
    void SetStyle(DWORD dStyle);

protected:

    void UpdateWindow();

    HWND    m_hWnd = nullptr;
    String	m_caption;
    uint32	m_width = 1024;
    uint32 	m_height = 768;
    uint32 	m_left = 200;
    uint32  m_top = 150;

    DWORD	m_style = WS_OVERLAPPEDWINDOW;
    WndProc m_wndProc;
};

OC_NS_END;