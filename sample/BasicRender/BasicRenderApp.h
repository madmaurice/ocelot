
#pragma once

#include "app/application.h"

OC_NS_BG;

class BasicRenderApp : public Application
{
public:
    BasicRenderApp();
    virtual ~BasicRenderApp();

private:
    virtual bool initializeImpl();
    virtual void shutdownImpl();

    virtual void updateImpl(float elapsed);
};

OC_NS_END;