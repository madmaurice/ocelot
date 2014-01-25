
#include "logFormatter.h"
#include <sstream>
#include <iomanip>
#include <ctime>

OC_NS_BG;

namespace LogFormatterImpl
{
    void appendCurrentTime(std::ostream& ostream)
    {
        std::time_t epoch = time(NULL);
        struct tm now;
        localtime_s(&now, &epoch);

        std::stringstream sstream;
        sstream << "(" << now.tm_hour << "h" << std::setfill('0') << std::setw(2) << now.tm_min 
                << ":" << std::setfill('0') << std::setw(2) << now.tm_sec << ")";

        ostream << sstream.str();
    }

    void appendLogLevel(std::ostream& ostream, LogLevel level)
    {
        std::string levelString(LogLevelHelper::logLeveltoString(level));
        std::string outString(6, ' '); //Max log level length is 6
        outString.replace(0, levelString.size(), levelString);

        ostream << "[" << outString << "]";
    }
}

ILogFormatter::~ILogFormatter()
{
}

LogFormatter::~LogFormatter()
{
}

void LogFormatter::applyFormat(const LogEvent& logEvent, std::ostream& ostream)
{
    LogFormatterImpl::appendCurrentTime(ostream);
    ostream << " - ";
    LogFormatterImpl::appendLogLevel(ostream, logEvent.m_logLevel);
    ostream << " : " << logEvent.m_message;
}

OC_NS_END;