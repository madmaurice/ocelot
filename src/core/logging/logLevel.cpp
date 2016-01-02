
#pragma once

#include "LogLevel.h"

OC_NS_BG;

String LogLevelUtil::LogLeveltoString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::Debug:
        return "Debug";
    case LogLevel::Info:
        return "Info";
    case LogLevel::Warn:
        return "Warn";
    case LogLevel::Error:
        return "Error";
    case LogLevel::Always:
        return "Always";
    default:
        {
        }
        return "";
    }
}

OC_NS_END;

