
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
    virtual void setFormatter(const std::shared_ptr<ILogFormatter>& formatter) = 0;
};

class LogAppenderBase : public ILogAppender
{
public:
    LogAppenderBase();
    LogAppenderBase(const std::shared_ptr<ILogFormatter>& formatter);
    virtual ~LogAppenderBase();

    virtual std::string getName() = 0;
    virtual void append(LogEvent logEvent) = 0;

    virtual ILogFormatter& getFormatter();
    virtual void setFormatter(const std::shared_ptr<ILogFormatter>& formatter);
protected:
    std::string formatLogEvent(LogEvent logEvent);

    std::shared_ptr<ILogFormatter> m_formatter;
};

class DebugConsoleAppender : public LogAppenderBase
{
public:
    DebugConsoleAppender();
    DebugConsoleAppender(const std::shared_ptr<ILogFormatter>& formatter);

    virtual std::string getName();
    virtual void append(LogEvent logEvent);
};

class StdOutAppender : public LogAppenderBase
{
public:
    StdOutAppender();
    StdOutAppender(const std::shared_ptr<ILogFormatter>& formatter);

    virtual std::string getName();
    virtual void append(LogEvent logEvent);
};

OC_NS_END;