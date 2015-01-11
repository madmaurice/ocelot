
#pragma once

// http://msdn.microsoft.com/en-us/library/b0084kay.aspx

#if defined(OC_LOG_ENABLED)

#include <sstream>
#include "logger.h"
#define _OC_LOG(level, msg, file, line)                                                \
    {                                                                   \
        std::stringstream sstream;                                      \
        sstream << msg;  \
        oc::Logger::getInstance().##level(sstream.str(), file, line);\
    }

#define OC_LOG(level, msg) _OC_LOG(debug, msg, __FILE__, __LINE__)
#define OC_LOG_DEBUG(msg) _OC_LOG(debug, msg, __FILE__, __LINE__)
#define OC_LOG_INFO(msg) _OC_LOG(info, msg, __FILE__, __LINE__)
#define OC_LOG_WARN(msg) _OC_LOG(warn, msg, __FILE__, __LINE__)
#define OC_LOG_ERROR(msg) _OC_LOG(error, msg, __FILE__, __LINE__)
#define OC_LOG_ALWAYS(msg) _OC_LOG(always, msg, __FILE__, __LINE__)
#else
#define OC_LOG(level, msg) do { (void)level;(void)(msg); } while(0)
#define OC_LOG_DEBUG(msg) do { (void)(msg); } while(0)
#define OC_LOG_INFO(msg) do { (void)(msg); } while(0)
#define OC_LOG_WARN(msg) do { (void)(msg); } while(0)
#define OC_LOG_ERROR(msg) do { (void)(msg); } while(0)
#define OC_LOG_ALWAYS(msg) do { (void)(msg); } while(0)
#endif