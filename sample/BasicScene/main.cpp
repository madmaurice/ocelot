
#include "pch.h"
#include "app/Application.h"
#include "BasicSceneApp.h"

using namespace OC;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
                   PSTR cmdLine, int showCmd)
{
    //Configure debugging stuff
    OC_DBG_CONFIG();

    BasicSceneApp app;
    app.Initialize();

    app.Run();

    app.Shutdown();

    return 0;
}