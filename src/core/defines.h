
#pragma once

#define OC_NS_BG namespace oc {
#define OC_NS_END }

// http://stackoverflow.com/questions/1946445/c-c-how-to-use-the-do-while0-construct-without-compiler-warnings-like-c412
#define OC_UNUSED(x) \
    __pragma(warning(push))         \
    __pragma(warning(disable:4127)) \
    do { (void)(x); } while(0) \
    __pragma(warning(pop))

// Enable run-time memory check for debug builds.
// And configure assert report
// link: http://msdn.microsoft.com/en-US/library/8hyw4sy7(v=vs.80).aspx
#if defined(DEBUG) || defined(_DEBUG)

#define OC_DEBUG
#define OC_LOG_ENABLED

#define OC_DBG_CONFIG() \
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); \
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_WNDW);
#else
#define OC_DBG_CONFIG()
#endif