
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

LogAppenderBase::~LogAppenderBase()
{
}

ILogFormatter& LogAppenderBase::getFormatter()
{
    return *m_formatter;
}

void LogAppenderBase::setFormatter(std::unique_ptr<ILogFormatter> formatter)
{
    m_formatter = std::move(formatter);
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