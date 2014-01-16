
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

    void info(std::string msg, const char* file, uint32 line);
    //void debug(string, string, int);
    //void warning(string, string, int);
    //void error(string, string, int);
private:
    Logger();

    void processLog(LogLevel level, std::string msg, const char* file, uint32 line);

    LoggingConfig   m_config;
    bool            m_initialized;
};

OC_NS_END;