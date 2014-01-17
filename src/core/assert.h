
#pragma once

#include "types.h"


namespace oc
{
    void ocAssert(const char* msg, const char* file, uint32 line);
    void ocAssert(const char* check, const char* msg, const char* file, uint32 line);
}

#if defined(_DEBUG)

#define OC_ASSERT(check) \
    __pragma(warning(push))         \
    __pragma(warning(disable:4127)) \
    do \
    { \
        if (!(check)) \
        { \
            oc::ocAssert(#check, nullptr, __FILE__, __LINE__); \
            __debugbreak(); \
        } \
    } while(0) \
    __pragma(warning(pop))

#define OC_ASSERT_MSG(check, msg) \
    __pragma(warning(push))         \
    __pragma(warning(disable:4127)) \
    do \
    { \
        if (!(check)) \
        { \
            oc::ocAssert(#check, msg, __FILE__, __LINE__); \
            __debugbreak(); \
        } \
    } while(0) \
    __pragma(warning(pop))

#else
#define OC_ASSERT(check) OC_UNUSED(check);
#define OC_ASSERT_MSG(check, msg)  do { OC_UNUSED(check); OC_UNUSED(msg) } while(0)
#endif