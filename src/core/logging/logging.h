
#pragma once

// http://msdn.microsoft.com/en-us/library/b0084kay.aspx

#if defined(_DEBUG)
#define OC_LOG_ENABLED
#endif

#if defined(OC_LOG_ENABLED)

#include <sstream>
#define OC_LOG(level, msg, file, line)                                                \
    {                                                                   \
        std::stringstream sstream;                                      \
        sstream << msg;  \
        oc::Logger::getInstance().##level(sstream.str(), file, line);\
    }

#define OC_LOG_DEBUG(msg) OC_LOG(debug, msg, __FILE__, __LINE__)
#define OC_LOG_INFO(msg) OC_LOG(info, msg, __FILE__, __LINE__)
#define OC_LOG_WARN(msg) OC_LOG(warn, msg, __FILE__, __LINE__)
#define OC_LOG_ERROR(msg) OC_LOG(error, msg, __FILE__, __LINE__)
#define OC_LOG_ALWAYS(msg) OC_LOG(always, msg, __FILE__, __LINE__)
#else
#define OC_LOG_DEBUG(msg) do { (void)(msg); } while(0)
#define OC_LOG_INFO(msg) do { (void)(msg); } while(0)
#define OC_LOG_WARN(msg) do { (void)(msg); } while(0)
#define OC_LOG_ERROR(msg) do { (void)(msg); } while(0)
#define OC_LOG_ALWAYS(msg) do { (void)(msg); } while(0)
#endif