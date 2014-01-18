
#pragma once

#include "core/types.h"
#include "core/logging/logEvent.h"
#include "core/logging/logFormatter.h"
#include <string>
#include <memory>

OC_NS_BG;

class ILogAppender
{
public:
    virtual ~ILogAppender();
    virtual std::string getName() = 0;
    virtual void append(LogEvent logEvent) = 0;

    virtual ILogFormatter& getFormatter() = 0;
    virtual void setFormatter(std::unique_ptr<ILogFormatter> formatter) = 0;
};

class LogAppenderBase : public ILogAppender
{
public:
    LogAppenderBase();
    virtual ~LogAppenderBase();
    virtual std::string getName() = 0;
    virtual void append(LogEvent logEvent) = 0;

    virtual ILogFormatter& getFormatter();
    virtual void setFormatter(std::unique_ptr<ILogFormatter> formatter);
protected:
    std::string formatLogEvent(LogEvent logEvent);

    std::unique_ptr<ILogFormatter> m_formatter;
};

class DebugConsoleAppender : public LogAppenderBase
{
public:

    virtual std::string getName();
    virtual void append(LogEvent logEvent);
};

class StdOutAppender : public LogAppenderBase
{
public:

    virtual std::string getName();
    virtual void append(LogEvent logEvent);
};

OC_NS_END;