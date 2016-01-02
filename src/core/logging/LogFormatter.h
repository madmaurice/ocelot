
#pragma once

#include "logEvent.h"

OC_NS_BG;

class ILogFormatter
{
public:
    virtual ~ILogFormatter();

    virtual void ApplyFormat(const LogEvent& logEvent, std::ostream& ostream) = 0;
};


// Default LogFormatter
class LogFormatter : public ILogFormatter
{
public:
    virtual ~LogFormatter();

    virtual void ApplyFormat(const LogEvent& logEvent, std::ostream& ostream) override;
};

OC_NS_END;