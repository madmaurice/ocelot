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

LogLevel LoggingConfig::getLogLevel() const
{
    return m_configData->m_logLevel;
}

void LoggingConfig::setLogLevel(LogLevel level)
{
    m_configData->m_logLevel = level;
}

const std::vector<std::unique_ptr<ILogAppender> >& LoggingConfig::getAllAppenders() const
{
    return m_configData->m_appenders;
}

void LoggingConfig::addAppender(std::unique_ptr<ILogAppender> appender)
{
    ILogAppender* app = getAppender<ILogAppender>(appender->getName());
    OC_ASSERT_MSG(app == nullptr, std::string("Appender '" + appender->getName() + "' is already added").c_str());
    
    if (!app)
    {
        m_configData->m_appenders.push_back(std::move(appender));
    }
}

void LoggingConfig::removeAppender(const std::string& name)
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
        ++it;
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