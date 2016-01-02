
#include "LogAppender.h"
#include <iostream>
#include <windows.h>

OC_NS_BG;

ILogAppender::~ILogAppender()
{
}

LogAppenderBase::LogAppenderBase()
    : m_formatter(new LogFormatter())
{
}

LogAppenderBase::LogAppenderBase(const std::shared_ptr<ILogFormatter>& formatter)
    : m_formatter(formatter)
{
}

LogAppenderBase::~LogAppenderBase()
{
    int toto = 0;
    OC_UNUSED(toto);
}

ILogFormatter& LogAppenderBase::GetFormatter()
{
    return *m_formatter;
}

void LogAppenderBase::SetFormatter(const std::shared_ptr<ILogFormatter>& formatter)
{
    m_formatter = formatter;
}

String LogAppenderBase::FormatLogEvent(const LogEvent& logEvent)
{
    std::stringstream sstream;
    m_formatter->ApplyFormat(logEvent, sstream);
    return sstream.str();
}

String DebugConsoleAppender::GetName()
{
    return "DebugConsole";
}

void DebugConsoleAppender::Append(const LogEvent& logEvent)
{
    String logString = FormatLogEvent(logEvent) + "\n";
    OutputDebugString(logString.c_str());
}

DebugConsoleAppender::DebugConsoleAppender()
{

}

DebugConsoleAppender::DebugConsoleAppender(const std::shared_ptr<ILogFormatter>& formatter)
    : LogAppenderBase(formatter)
{

}

StdOutAppender::StdOutAppender()
{
}

StdOutAppender::StdOutAppender(const std::shared_ptr<ILogFormatter>& formatter)
    : LogAppenderBase(formatter)
{
}

String StdOutAppender::GetName()
{
    return "StdOut";
}

void StdOutAppender::Append(const LogEvent& logEvent)
{
    String logString = FormatLogEvent(logEvent);
    std::cout << logString << std::endl;
}


OC_NS_END;