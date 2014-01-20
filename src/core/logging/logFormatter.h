
#pragma once

#include "core/types.h"
#include <string>
#include "logEvent.h"

OC_NS_BG;

class ILogFormatter
{
public:
    virtual ~ILogFormatter();

    virtual ILogFormatter* clone() const = 0;
    virtual std::string applyFormat(LogEvent logEvent) = 0;
};


class LogFormatter : public ILogFormatter
{
public:
    virtual ~LogFormatter();

    virtual LogFormatter* clone() const;
    virtual std::string applyFormat(LogEvent logEvent);
};

// Wrap another formatter to add more functionality
// This takes ownership of the formatter received in the ctor
class LogFormatterWrapper : public ILogFormatter
{
public:
    explicit LogFormatterWrapper(ILogFormatter* formatter); //Takes ownership
    LogFormatterWrapper(const LogFormatterWrapper& other);
    virtual ~LogFormatterWrapper();

    LogFormatterWrapper& operator=(const LogFormatterWrapper& rhs);

    virtual LogFormatterWrapper* clone() const;
    virtual std::string applyFormat(LogEvent logEvent);

private:
    ILogFormatter* m_formatter;
};

class TimeFormatter : public LogFormatterWrapper
{
public:
    explicit TimeFormatter(ILogFormatter* formatter); //Takes ownership
    virtual ~TimeFormatter();

    virtual TimeFormatter* clone() const;
    virtual std::string applyFormat(LogEvent logEvent);
};


OC_NS_END;