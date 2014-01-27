
#include "logger.h"
#include "core/logging/logEvent.h"
#include <iostream>

OC_NS_BG;

Logger& Logger::getInstance()
{
    // Guaranteed to be destroyed.
    // Instantiated on first use.
    static Logger instance;
    return instance;
}

void Logger::init(const LoggingConfig& config)
{
    Logger& logger = getInstance();
    logger.m_config = config;
}

LoggingConfig& Logger::getConfig()
{
    return m_config;
}

void Logger::debug(std::string msg, const char* file, uint32 line)
{
    processLog(LogLevel::Debug, msg, file, line);
}

void Logger::info(std::string msg, const char* file, uint32 line)
{
    processLog(LogLevel::Info, msg, file, line);
}

void Logger::warn(std::string msg, const char* file, uint32 line)
{
    processLog(LogLevel::Warn, msg, file, line);
}

void Logger::error(std::string msg, const char* file, uint32 line)
{
    processLog(LogLevel::Error, msg, file, line);
}

void Logger::always(std::string msg, const char* file, uint32 line)
{
    processLog(LogLevel::Always, msg, file, line);
}

Logger::Logger()
{
}

void Logger::processLog(LogLevel level, std::string msg, const char* file, uint32 line)
{
    if (level >= m_config.getLogLevel())
    {
        LogEvent log(level, msg, file, line);

        for (auto& appender : m_config.getAllAppenders())
        {
            appender->append(log);
        }
    }
}



OC_NS_END;