#include "engine.h"
#include "app/application.h"
#include <functional>

OC_NS_BG;

Engine::Engine(const AppContext& appContext)
    : m_graphicSystem(appContext.m_hwnd, appContext.m_windowWidth, appContext.m_windowHeight)
    , m_eventDispatcher(appContext.m_eventDispatcher)
{
}

Engine::~Engine()
{
}

bool Engine::initialize()
{
    using namespace std::placeholders;

    OC_LOG_INFO("Engine initializing");

    if (!m_graphicSystem.initialize())
    {
        OC_LOG_ERROR("Engine initialization failed");
        return false;
    }

    Event::Callback callback = std::bind(&Engine::handleResize, this, _1);
    m_eventDispatcher->addEventHandler(Event::Type::WndResize, callback);

    OC_LOG_INFO("Engine initialize completed");
    return true;
}

void Engine::shutdown()
{
    m_graphicSystem.shutdown();
}

void Engine::update(float elapsed)
{
    OC_UNUSED(elapsed);
    // TODO : update stuffs
}

void Engine::clear()
{
    m_graphicSystem.clear();
}

void Engine::render()
{
    m_graphicSystem.present();
}

void Engine::handleResize(EventPtr resizeEvent)
{
    OC_ASSERT(resizeEvent->m_type == Event::Type::WndResize);
    ResizeEvent* event = static_cast<ResizeEvent*>(resizeEvent.get());
    m_graphicSystem.resize(event->m_width, event->m_height);
}


OC_NS_END;