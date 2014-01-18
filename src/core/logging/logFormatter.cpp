
#include "logFormatter.h"
#include <sstream>

OC_NS_BG;


ILogFormatter::~ILogFormatter()
{
}

LogFormatter::~LogFormatter()
{
}

LogFormatter* LogFormatter::clone()
{
    return new LogFormatter(*this);
}

std::string LogFormatter::applyFormat(LogEvent logEvent)
{
    //TODO
    std::stringstream sstream;
    sstream << logEvent;
    return sstream.str();
}


OC_NS_END;