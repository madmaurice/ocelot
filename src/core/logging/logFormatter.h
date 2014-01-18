
#pragma once

#include "core/types.h"
#include <string>
#include "logEvent.h"

OC_NS_BG;

class ILogFormatter
{
public:
    virtual ~ILogFormatter();
    virtual ILogFormatter* clone() = 0;
    virtual std::string applyFormat(LogEvent logEvent) = 0;
};

class LogFormatter : public ILogFormatter
{
public:
    virtual ~LogFormatter();
    virtual LogFormatter* clone();
    virtual std::string applyFormat(LogEvent logEvent);
};

OC_NS_END;