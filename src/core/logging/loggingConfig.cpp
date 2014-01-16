#include "loggingConfig.h"

OC_NS_BG;

LoggingConfig::LoggingConfig()
    : m_logLevel(LogLevel::Info)
{
}

LoggingConfig::~LoggingConfig()
{
}

LogLevel LoggingConfig::getLogLevel()
{
    return m_logLevel;
}

void LoggingConfig::setLogLevel( LogLevel level )
{
    m_logLevel = level;
}


OC_NS_END;