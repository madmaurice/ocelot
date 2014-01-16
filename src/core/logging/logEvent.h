
#pragma once

#include "core/types.h"
#include "core/logging/logLevel.h"
#include <string>

OC_NS_BG;

struct LogEvent
{
    LogEvent();
    LogEvent(LogLevel logLevel);
    LogEvent(LogLevel logLevel, std::string msg);
    LogEvent(LogLevel logLevel, std::string msg, std::string file);
    LogEvent(LogLevel logLevel, std::string msg, std::string file, uint32 line);

    LogLevel        m_logLevel;
    std::string     m_category;
    std::string     m_message;
    std::string     m_file;
    uint32          m_lineNumber;
};

OC_NS_END;