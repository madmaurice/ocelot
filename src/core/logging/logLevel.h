
#pragma once

OC_NS_BG;

enum class LogLevel
{
    Debug = 0,
    Info,
    Warn,
    Error,
    Always
};

namespace LogLevelUtil
{
    std::string logLeveltoString(LogLevel level);
};

OC_NS_END;

