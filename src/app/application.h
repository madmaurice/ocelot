
#pragma once

#include "app/fpsCounter.h"
#include "app/window.h"
#include "core/system/timer.h"

OC_NS_BG;

struct AppContext
{
    HWND m_hwnd;
    uint32 m_windowWidth;
    uint32 m_windowHeight;
};

class Engine;

class Application : public NonCopyable
{
public:
    Application(const String& name);
    virtual ~Application();

    bool initialize();
    bool initialize(const LoggingConfig& config);

    void shutdown();

    // Starts main loop
    void run();

private:

    virtual bool initializeImpl() = 0;
    virtual void shutdownImpl() = 0;

    virtual void updateImpl(float elapsed) = 0;

    // Called each frame
    void update();

    void handleResize(uint32 width, uint32 height);

    LRESULT wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    bool m_paused;
    bool m_resizing;
    bool m_minimized;
    bool m_maximized;
    bool m_shutdown;
    bool m_initCompleted;

    Timer m_timer;
    FpsCounter m_fpsCounter;

    std::unique_ptr<Engine> m_engine;

    Window m_window;
    const String m_name;
};

OC_NS_END;