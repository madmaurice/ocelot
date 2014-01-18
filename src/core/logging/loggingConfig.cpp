#include "loggingConfig.h"
#include "core/assert.h"

OC_NS_BG;

LoggingConfig::LoggingConfig()
    : m_configData(new ConfigInternal())
{
}

LoggingConfig::LoggingConfig(LogLevel defaultLogLevel)
    : m_configData(new ConfigInternal(defaultLogLevel))
{
}

LoggingConfig::~LoggingConfig()
{
}

LogLevel LoggingConfig::getLogLevel()
{
    return m_configData->m_logLevel;
}

void LoggingConfig::setLogLevel(LogLevel level)
{
    m_configData->m_logLevel = level;
}

std::vector<std::unique_ptr<ILogAppender> >& LoggingConfig::getAllAppenders()
{
    return m_configData->m_appenders;
}

ILogAppender* LoggingConfig::getAppender(std::string name)
{
    for (const auto& appender : m_configData->m_appenders)
    {
        if (appender->getName() == name)
        {
            return appender.get();
        }
    }
    return nullptr;
}

void LoggingConfig::addAppender(std::unique_ptr<ILogAppender> appender)
{
    ILogAppender* app = getAppender(appender->getName());
    OC_ASSERT_MSG(app == nullptr, std::string("Appender '" + appender->getName() + "' is already added").c_str());
    
    if (!app)
    {
        m_configData->m_appenders.push_back(std::move(appender));
    }
}

void LoggingConfig::removeAppender(std::string name)
{
    auto& vect = m_configData->m_appenders;
    auto it = std::begin(vect);

    while (it != std::end(vect)) 
    {
        if ((*it)->getName() == name)
        {
            vect.erase(it);
            return;
        }
    }
}

LoggingConfig::ConfigInternal::ConfigInternal()
    : m_logLevel(LogLevel::Info)
{
}

LoggingConfig::ConfigInternal::ConfigInternal(LogLevel level)
    : m_logLevel(level)
{
}

OC_NS_END;