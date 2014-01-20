
#include "logAppender.h"
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

ILogFormatter& LogAppenderBase::getFormatter()
{
    return *m_formatter;
}

void LogAppenderBase::setFormatter(const std::shared_ptr<ILogFormatter>& formatter)
{
    m_formatter = formatter;
}

std::string LogAppenderBase::formatLogEvent(LogEvent logEvent)
{
    return m_formatter->applyFormat(logEvent);
}

std::string DebugConsoleAppender::getName()
{
    return "DebugConsole";
}

void DebugConsoleAppender::append(LogEvent logEvent)
{
    std::string logString = formatLogEvent(logEvent);
    OutputDebugString(logString.c_str());
}

DebugConsoleAppender::DebugConsoleAppender()
{

}

DebugConsoleAppender::DebugConsoleAppender(const std::shared_ptr<ILogFormatter>& formatter)
    : LogAppenderBase(formatter)
{

}StdOutAppender::StdOutAppender()
{
}

StdOutAppender::StdOutAppender(const std::shared_ptr<ILogFormatter>& formatter)
    : LogAppenderBase(formatter)
{
    int toto;
    OC_UNUSED(toto);
}

std::string StdOutAppender::getName()
{
    return "StdOut";
}

void StdOutAppender::append(LogEvent logEvent)
{
    std::string logString = formatLogEvent(logEvent);
    std::cout << logString << std::endl;
}


OC_NS_END;