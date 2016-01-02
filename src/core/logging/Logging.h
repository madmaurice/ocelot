
#pragma once

// http://msdn.microsoft.com/en-us/library/b0084kay.aspx

#if defined(OC_LOG_ENABLED)

#include <sstream>
#include "Logger.h"
#define _OC_LOG(level, msg, file, line)                                                \
    {                                                                   \
        std::stringstream sstream;                                      \
        sstream << msg;  \
        OC::Logger::GetInstance().##level(sstream.str(), file, line);\
    }

#define OC_LOG(level, msg) _OC_LOG(level, msg, __FILE__, __LINE__)
#define OC_LOG_DEBUG(msg) _OC_LOG(Debug, msg, __FILE__, __LINE__)
#define OC_LOG_INFO(msg) _OC_LOG(Info, msg, __FILE__, __LINE__)
#define OC_LOG_WARN(msg) _OC_LOG(Warn, msg, __FILE__, __LINE__)
#define OC_LOG_ERROR(msg) _OC_LOG(Error, msg, __FILE__, __LINE__)
#define OC_LOG_ALWAYS(msg) _OC_LOG(Always, msg, __FILE__, __LINE__)
#else
#define OC_LOG(level, msg) do { (void)level;(void)(msg); } while(0)
#define OC_LOG_DEBUG(msg) do { (void)(msg); } while(0)
#define OC_LOG_INFO(msg) do { (void)(msg); } while(0)
#define OC_LOG_WARN(msg) do { (void)(msg); } while(0)
#define OC_LOG_ERROR(msg) do { (void)(msg); } while(0)
#define OC_LOG_ALWAYS(msg) do { (void)(msg); } while(0)
#endif