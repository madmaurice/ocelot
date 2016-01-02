
#pragma once

#include "core/logging/LoggingConfig.h"
#include "core/logging/LogLevel.h"
#include <string>

OC_NS_BG;

class Logger
{
public:
    static Logger& GetInstance();

    static void Init(const LoggingConfig& config);

    LoggingConfig& GetConfig();

    void Debug(const String& msg, const char* file, uint32 line);
    void Info(const String& msg, const char* file, uint32 line);
    void Warn(const String& msg, const char* file, uint32 line);
    void Error(const String& msg, const char* file, uint32 line);
    void Always(const String& msg, const char* file, uint32 line);

private:
    Logger();

    void ProcessLog(LogLevel level, const String& msg, const char* file, uint32 line);

    LoggingConfig   m_config;
};

OC_NS_END;