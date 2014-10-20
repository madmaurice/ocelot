
#include "BasicRenderApp.h"

OC_NS_BG;


BasicRenderApp::BasicRenderApp()
    : Application("Basic render")
{
}

BasicRenderApp::~BasicRenderApp()
{
}

bool BasicRenderApp::initializeImpl()
{
    return true;
}

void BasicRenderApp::shutdownImpl()
{
}

void BasicRenderApp::updateImpl(float elapsed)
{
    OC_UNUSED(elapsed);
}

OC_NS_END;