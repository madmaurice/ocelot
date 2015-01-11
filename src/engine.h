
#pragma once

#include "graphic/graphicSystem.h"
#include "core/util/nonCopyable.h"

OC_NS_BG;

struct AppContext;

class Engine : public NonCopyable
{
public:
    Engine(const AppContext& appContext);
    ~Engine();

    bool initialize();
    void shutdown();

    void runFrame(float elapsed);

    // TODO : better propagate
    void resize(uint32 width, uint32 height);

private:
    GraphicSystem m_graphicSystem;
};

OC_NS_END;