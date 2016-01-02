
#include "LogEvent.h"

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

std::ostream& operator<<(std::ostream& stream, const LogEvent& logEvent)
{
    stream << "Level : " << LogLevelUtil::LogLeveltoString(logEvent.m_logLevel) << std::endl;
    stream << "Message : " << logEvent.m_message << std::endl;
    stream << "File : " << logEvent.m_file << std::endl;
    stream << "Line : " << logEvent.m_lineNumber << std::endl;
    return stream;
}

OC_NS_END;