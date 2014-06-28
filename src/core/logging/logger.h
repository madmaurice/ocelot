
#pragma once

#include "core/logging/loggingConfig.h"
#include "core/logging/logLevel.h"
#include <string>

OC_NS_BG;

class Logger
{
public:
    static Logger& getInstance();

    static void init(const LoggingConfig& config);

    LoggingConfig& getConfig();

    void debug(std::string msg, const char* file, uint32 line);
    void info(std::string msg, const char* file, uint32 line);
    void warn(std::string msg, const char* file, uint32 line);
    void error(std::string msg, const char* file, uint32 line);
    void always(std::string msg, const char* file, uint32 line);

private:
    Logger();

    void processLog(LogLevel level, std::string msg, const char* file, uint32 line);

    LoggingConfig   m_config;
};

OC_NS_END;