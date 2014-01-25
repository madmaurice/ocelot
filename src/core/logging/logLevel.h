
#pragma once

#include "core/common.h"

OC_NS_BG;

enum class LogLevel
{
    Debug = 0,
    Info,
    Warn,
    Error,
    Always
};

namespace LogLevelHelper
{
    std::string logLeveltoString(LogLevel level);
};

OC_NS_END;
