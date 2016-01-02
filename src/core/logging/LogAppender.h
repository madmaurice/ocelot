
#pragma once

#include "core/logging/LogEvent.h"
#include "core/logging/LogFormatter.h"
#include <memory>

OC_NS_BG;

class ILogAppender
{
public:
    virtual ~ILogAppender();
    virtual String GetName() = 0;
    virtual void Append(const LogEvent& logEvent) = 0;

    virtual ILogFormatter& GetFormatter() = 0;
    virtual void SetFormatter(const std::shared_ptr<ILogFormatter>& formatter) = 0;
};

class LogAppenderBase : public ILogAppender
{
public:
    LogAppenderBase();
    LogAppenderBase(const std::shared_ptr<ILogFormatter>& formatter);
    virtual ~LogAppenderBase();

    ILogFormatter& GetFormatter();
    void SetFormatter(const std::shared_ptr<ILogFormatter>& formatter);

protected:
    String FormatLogEvent(const LogEvent& logEvent);

    std::shared_ptr<ILogFormatter> m_formatter;
};

class DebugConsoleAppender : public LogAppenderBase
{
public:
    DebugConsoleAppender();
    DebugConsoleAppender(const std::shared_ptr<ILogFormatter>& formatter);

    virtual String GetName() override;
    virtual void Append(const LogEvent& logEvent) override;
};

class StdOutAppender : public LogAppenderBase
{
public:
    StdOutAppender();
    StdOutAppender(const std::shared_ptr<ILogFormatter>& formatter);

    virtual String GetName() override;
    virtual void Append(const LogEvent& logEvent) override;
};

OC_NS_END;