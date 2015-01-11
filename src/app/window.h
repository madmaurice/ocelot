
#pragma once

#include "core/util/nonCopyable.h"
#include <windows.h>
#include <functional>


OC_NS_BG;

class Window : public NonCopyable
{
public:
    typedef std::function<LRESULT(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)> WndProc;

    explicit Window(const String& caption = "OCWindow");
    ~Window();

    bool initialize(WndProc wndProc);
    void shutdown();

    HWND getHandle();

    void setWidth(uint32 width);
    void setHeight(uint32 height);

    int getWidth();
    int getHeight();

    int getLeft();
    int getTop();

    void setSize(uint32 width, uint32 height);
    void setPosition(uint32 left, uint32 top);

    void resize(int width, int height);

    void setCaption(const String& caption);
    void setStyle(DWORD dStyle);

protected:

    void updateWindow();

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