
#include "pch.h"
#include "app/application.h"
#include "BasicRenderApp.h"

using namespace oc;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
                   PSTR cmdLine, int showCmd)
{
    //Configure debugging stuff
    OC_DBG_CONFIG();

    BasicRenderApp app;

    if (!app.initialize())
    {
        MessageBox(NULL, "Init failed", NULL, MB_ICONERROR | MB_SYSTEMMODAL);
        return 1;
    }

    app.run();

    return 0;
}