
#include "LogFormatter.h"
#include <sstream>
#include <iomanip>
#include <ctime>

OC_NS_BG;

namespace LogFormatterImpl
{
    void AppendCurrentTime(std::ostream& ostream)
    {
        std::time_t epoch = time(NULL);
        struct tm now;
        localtime_s(&now, &epoch);

        char buffer[11];
        strftime(buffer, 11, "(%Hh%M:%S)", &now);
        ostream << buffer;
    }

    void AppendLogLevel(std::ostream& ostream, LogLevel level)
    {
        std::string levelString(LogLevelUtil::LogLeveltoString(level));
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

void LogFormatter::ApplyFormat(const LogEvent& logEvent, std::ostream& ostream)
{
    LogFormatterImpl::AppendCurrentTime(ostream);
    ostream << " - ";
    LogFormatterImpl::AppendLogLevel(ostream, logEvent.m_logLevel);
    ostream << " : " << logEvent.m_message;
}

OC_NS_END;