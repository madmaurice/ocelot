
#pragma once

#include "app/Window.h"
#include "core/system/Timer.h"
#include "graphic/Graphic.h"

OC_NS_BG;

class Application : public NonCopyable
{
public:
    Application(const String& name);
    virtual ~Application();

    bool Initialize();
    bool Initialize(const LoggingConfig& config);

    void Shutdown();

    // Starts main loop
    void Run();

private:

    virtual bool InitializeImpl() = 0;
    virtual void ShutdownImpl() = 0;

    virtual void UpdateImpl(float elapsed) = 0;
    virtual void RenderImpl() = 0;

    // Called each frame
    void Update(float elapsed);
    void Render();

    void Pause();
    void Unpause();

    void OnResize(uint32 width, uint32 height);

    LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    Timer m_timer;

protected:
    Window m_window;
    const String m_name;

private:

    bool m_paused;
    bool m_resizing;
    bool m_minimized;
    bool m_maximized;
    bool m_shutdown;
    bool m_initCompleted;
};

OC_NS_END;