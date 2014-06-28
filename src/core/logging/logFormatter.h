
#pragma once

#include "logEvent.h"

OC_NS_BG;

class ILogFormatter
{
public:
    virtual ~ILogFormatter();

    virtual void applyFormat(const LogEvent& logEvent, std::ostream& ostream) = 0;
};


// Default LogFormatter
class LogFormatter : public ILogFormatter
{
public:
    virtual ~LogFormatter();

    virtual void applyFormat(const LogEvent& logEvent, std::ostream& ostream);
};

OC_NS_END;