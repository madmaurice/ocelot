
#include "logEvent.h"

OC_NS_BG;

LogEvent::LogEvent()
{
}

LogEvent::LogEvent(LogLevel logLevel)
    : m_logLevel(logLevel)
{
}

LogEvent::LogEvent(LogLevel logLevel, std::string msg)
    : m_logLevel(logLevel)
    , m_message(msg)
{
}

LogEvent::LogEvent(LogLevel logLevel, std::string msg, std::string file)
    : m_logLevel(logLevel)
    , m_message(msg)
    , m_file(file)
{
}

LogEvent::LogEvent(LogLevel logLevel, std::string msg, std::string file, uint32 line)
    : m_logLevel(logLevel)
    , m_message(msg)
    , m_file(file)
    , m_lineNumber(line)
{
}

OC_NS_END;