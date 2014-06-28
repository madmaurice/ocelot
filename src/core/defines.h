
#pragma once

#define OC_NS_BG namespace oc {
#define OC_NS_END }


// http://stackoverflow.com/questions/1946445/c-c-how-to-use-the-do-while0-construct-without-compiler-warnings-like-c412
#define OC_UNUSED(x) \
    __pragma(warning(push))         \
    __pragma(warning(disable:4127)) \
    do { (void)(x); } while(0) \
    __pragma(warning(pop))

// Define unique_ptr implementation : http://stackoverflow.com/questions/13883824/make-unique-does-not-compile
#include <memory> // brings in TEMPLATE macros.

#define _MAKE_UNIQUE(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4)  \
    namespace oc {\
        template<class T COMMA LIST(_CLASS_TYPE)>    \
        inline std::unique_ptr<T> make_unique(LIST(_TYPE_REFREF_ARG))    \
        {    \
            return std::unique_ptr<T>(new T(LIST(_FORWARD_ARG)));    \
        }\
    };

_VARIADIC_EXPAND_0X(_MAKE_UNIQUE, , , , )
#undef _MAKE_UNIQUE