
#pragma once

#include "app/event.h"
#include "core/util/nonCopyable.h"
#include "graphic/graphicSystem.h"

OC_NS_BG;

struct AppContext;

class Engine : public NonCopyable
{
public:
    Engine(const AppContext& appContext);
    ~Engine();

    bool initialize();
    void shutdown();

    void update(float elapsed);
    void clear();
    void render();

    // TODO : remove methods below
    GraphicSystem* getGraphics() { return &m_graphicSystem; }

private:
    void handleResize(EventPtr resizeEvent);

    GraphicSystem m_graphicSystem;

    std::shared_ptr<EventDispatcher> m_eventDispatcher;
};

OC_NS_END;