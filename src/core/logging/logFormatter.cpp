
#include "logFormatter.h"
#include <sstream>
#include <ctime>

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

LogFormatter* LogFormatter::clone() const
{
    return new LogFormatter(*this);
}

//-----------------------------------------------------------------------------
// LogFormatterDecorator

LogFormatterWrapper::LogFormatterWrapper(ILogFormatter* formatter)
    : m_formatter(formatter)
{
}

LogFormatterWrapper::LogFormatterWrapper(const LogFormatterWrapper& other)
    : m_formatter(other.m_formatter->clone())
{
}

LogFormatterWrapper::~LogFormatterWrapper()
{
    delete m_formatter;
}

LogFormatterWrapper& LogFormatterWrapper::operator=(const LogFormatterWrapper& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    delete m_formatter;
    m_formatter = rhs.m_formatter->clone();
    return *this;
}

std::string LogFormatterWrapper::applyFormat(LogEvent logEvent)
{
    return m_formatter->applyFormat(logEvent);
}

LogFormatterWrapper* LogFormatterWrapper::clone() const
{
    return new LogFormatterWrapper(*this);
}

//-----------------------------------------------------------------------------
// TimeFormatter

TimeFormatter::TimeFormatter(ILogFormatter* formatter)
    : LogFormatterWrapper(formatter)
{
}

TimeFormatter::~TimeFormatter()
{
}

TimeFormatter* TimeFormatter::clone() const
{
    return new TimeFormatter(*this);
}

std::string TimeFormatter::applyFormat(LogEvent logEvent)
{
    const std::string& base = LogFormatterWrapper::applyFormat(logEvent);

    std::time_t epoch = time(NULL);
    struct tm now;
    localtime_s(&now, &epoch);

    std::stringstream sstream;
    sstream << "[ " << now.tm_hour << "h" << now.tm_min << ":" << now.tm_sec << " ]";

    return sstream.str() + "  " + base;
}

OC_NS_END;