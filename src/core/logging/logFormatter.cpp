
#include "logFormatter.h"
#include <sstream>

OC_NS_BG;


ILogFormatter::~ILogFormatter()
{
}

LogFormatter::~LogFormatter()
{
}

std::string LogFormatter::applyFormat(LogEvent logEvent)
{
    //TODO
    //std::stringstream sstream;
    //sstream << logEvent;
    //return sstream.str();
    return logEvent.m_message;
}

//-----------------------------------------------------------------------------
// LogFormatterDecorator

LogFormatterWrapper::LogFormatterWrapper(FormatterPtr formatter)
    : m_formatter(formatter)
{
}

LogFormatterWrapper::~LogFormatterWrapper()
{
}

std::string LogFormatterWrapper::applyFormat(LogEvent logEvent)
{
    return m_formatter->applyFormat(logEvent);
}
//-----------------------------------------------------------------------------
// TimeFormatter

TimeFormatter::TimeFormatter(FormatterPtr formatter)
    : LogFormatterWrapper(formatter)
{
}

TimeFormatter::~TimeFormatter()
{
}

std::string TimeFormatter::applyFormat(LogEvent logEvent)
{
    const std::string& base = LogFormatterWrapper::applyFormat(logEvent);
    return "Current time " + base;
}


OC_NS_END;