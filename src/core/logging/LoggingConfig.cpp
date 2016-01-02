#include "loggingConfig.h"

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

LogLevel LoggingConfig::GetLogLevel() const
{
    return m_configData->m_logLevel;
}

void LoggingConfig::SetLogLevel(LogLevel level)
{
    m_configData->m_logLevel = level;
}

const Vector<std::unique_ptr<ILogAppender> >& LoggingConfig::GetAllAppenders() const
{
    return m_configData->m_appenders;
}

void LoggingConfig::AddAppender(std::unique_ptr<ILogAppender> appender)
{
    ILogAppender* app = GetAppender<ILogAppender>(appender->GetName());
    OC_ASSERT_MSG(app == nullptr, String("Appender '" + appender->GetName() + "' is already added").c_str());
    
    if (!app)
    {
        m_configData->m_appenders.push_back(std::move(appender));
    }
}

void LoggingConfig::RemoveAppender(const String& name)
{
    auto& vect = m_configData->m_appenders;
    auto it = std::begin(vect);

    while (it != std::end(vect)) 
    {
        if ((*it)->GetName() == name)
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