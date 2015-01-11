#include "engine.h"
#include "app/application.h"

OC_NS_BG;

Engine::Engine(const AppContext& appContext)
    : m_graphicSystem(appContext.m_hwnd, appContext.m_windowWidth, appContext.m_windowHeight)
{
}

Engine::~Engine()
{
}

bool Engine::initialize()
{
    OC_LOG_INFO("Engine initializing");

    if (!m_graphicSystem.initialize())
    {
        OC_LOG_ERROR("Engine initialization failed");
        return false;
    }

    OC_LOG_INFO("Engine initialize completed");
    return true;
}

void Engine::shutdown()
{
    m_graphicSystem.shutdown();
}

void Engine::runFrame(float elapsed)
{
    OC_UNUSED(elapsed);
    // TODO : draw stuffs
    m_graphicSystem.present();
}

void Engine::resize(uint32 width, uint32 height)
{
    m_graphicSystem.resize(width, height);
}

OC_NS_END;