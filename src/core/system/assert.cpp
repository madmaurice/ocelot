
#include "assert.h"
#include "core/logging/logger.h"
#include <sstream>
#include <windows.h>

void oc::ocAssert(const char* check, const char* msg, const char* file, uint32 line)
{
    std::stringstream sstream;
    sstream << "Assertion failed : '" << check << "' in " << file << ":" << line;
    if (msg)
    {
        sstream << " Why : " << msg;
    }

    if (IsDebuggerPresent())
    {
        OutputDebugStringA(sstream.str().c_str());
    }
    else
    {
        MessageBoxA(nullptr, sstream.str().c_str(), "Assert !", MB_OK | MB_ICONERROR);
    }
}

void oc::ocAssert(const char* msg, const char* file, uint32 line)
{
    std::stringstream sstream;
    sstream << "Assertion failed : '" << msg << "' in " << file << ":" << line;

    if (IsDebuggerPresent())
    {
        OutputDebugStringA(sstream.str().c_str());
    }
    else
    {
        MessageBoxA(nullptr, sstream.str().c_str(), "Assert !", MB_OK | MB_ICONERROR);
    }
}

