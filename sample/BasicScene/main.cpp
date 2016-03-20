
#include "pch.h"
#include "app/Application.h"
#include "BasicSceneApp.h"

using namespace OC;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
                   PSTR cmdLine, int showCmd)
{
    //Configure debugging stuff
    OC_DBG_CONFIG();

    std::string str("Hello");
    size_t toto = std::hash<std::string>()(str);

    // TODO : StringHash

    return 0;
}