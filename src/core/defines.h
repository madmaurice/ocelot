
#pragma once

#define OC_NS_BG namespace oc {
#define OC_NS_END }


// http://stackoverflow.com/questions/1946445/c-c-how-to-use-the-do-while0-construct-without-compiler-warnings-like-c412
#define OC_UNUSED(x) \
    __pragma(warning(push))         \
    __pragma(warning(disable:4127)) \
    do { (void)(x); } while(0) \
    __pragma(warning(pop))