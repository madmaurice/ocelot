
#pragma once

#include "logLevel.h"

OC_NS_BG;

std::string LogLevelUtil::logLeveltoString(LogLevel level)
{
    switch (level)
    {
    case oc::LogLevel::Debug:
        return "Debug";
    case oc::LogLevel::Info:
        return "Info";
    case oc::LogLevel::Warn:
        return "Warn";
    case oc::LogLevel::Error:
        return "Error";
    case oc::LogLevel::Always:
        return "Always";
    default:
        {
            //OC_ASSERT_FORCE("Unknown log level");
        }
        return "";
    }
}

OC_NS_END;

