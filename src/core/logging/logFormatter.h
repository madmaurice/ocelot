
#pragma once

#include "core/types.h"
#include <string>
#include "logEvent.h"

OC_NS_BG;


class ILogFormatter
{
public:
    virtual ~ILogFormatter();
    virtual std::string applyFormat(LogEvent logEvent) = 0;
};

typedef std::shared_ptr<ILogFormatter> FormatterPtr;

class LogFormatter : public ILogFormatter
{
public:
    virtual ~LogFormatter();
    virtual std::string applyFormat(LogEvent logEvent);
};

class LogFormatterWrapper : public ILogFormatter
{
public:
    explicit LogFormatterWrapper(FormatterPtr formatter);
    virtual ~LogFormatterWrapper();

    virtual std::string applyFormat(LogEvent logEvent);
private:

    FormatterPtr m_formatter;
};

class TimeFormatter : public LogFormatterWrapper
{
public:
    explicit TimeFormatter(FormatterPtr formatter);
    virtual ~TimeFormatter();

    virtual std::string applyFormat(LogEvent logEvent);
private:
};

OC_NS_END;