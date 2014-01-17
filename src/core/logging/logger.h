
#pragma once

#include "core/common.h"
#include "core/logging/loggingConfig.h"
#include "core/logging/logLevel.h"
#include <string>

OC_NS_BG;

class Logger
{
public:
    static Logger& getInstance();

    static bool init(const LoggingConfig& config);
    static void uninit();

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
    bool            m_initialized;
};

OC_NS_END;