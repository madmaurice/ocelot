
#include "Logger.h"
#include "core/logging/LogEvent.h"
#include <iostream>

OC_NS_BG;

Logger& Logger::GetInstance()
{
    // Guaranteed to be destroyed.
    // Instantiated on first use.
    static Logger instance;
    return instance;
}

void Logger::Init(const LoggingConfig& config)
{
    Logger& logger = GetInstance();
    logger.m_config = config;
}

LoggingConfig& Logger::GetConfig()
{
    return m_config;
}

void Logger::Debug(const String& msg, const char* file, uint32 line)
{
    ProcessLog(LogLevel::Debug, msg, file, line);
}

void Logger::Info(const String& msg, const char* file, uint32 line)
{
    ProcessLog(LogLevel::Info, msg, file, line);
}

void Logger::Warn(const String& msg, const char* file, uint32 line)
{
    ProcessLog(LogLevel::Warn, msg, file, line);
}

void Logger::Error(const String& msg, const char* file, uint32 line)
{
    ProcessLog(LogLevel::Error, msg, file, line);
}

void Logger::Always(const String& msg, const char* file, uint32 line)
{
    ProcessLog(LogLevel::Always, msg, file, line);
}

Logger::Logger()
{
}

void Logger::ProcessLog(LogLevel level, const String& msg, const char* file, uint32 line)
{
    if (level >= m_config.GetLogLevel())
    {
        LogEvent log(level, msg, file, line);

        for (auto& appender : m_config.GetAllAppenders())
        {
            appender->Append(log);
        }
    }
}



OC_NS_END;