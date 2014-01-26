//---------------------------------------------------------------------------------------
//
// Logging configuration that is shared on copy
//
//---------------------------------------------------------------------------------------
#pragma once

#include "core/common.h"
#include "core/logging/logAppender.h"
#include "core/logging/logLevel.h"
#include <memory>
#include <vector>

OC_NS_BG;

class LoggingConfig
{
public:
    LoggingConfig();
    explicit LoggingConfig(LogLevel defaultLogLevel);

    ~LoggingConfig();

    LogLevel getLogLevel() const;
    void setLogLevel(LogLevel level);

    const std::vector<std::unique_ptr<ILogAppender> >& getAllAppenders() const;

    template<class T>
    T* getAppender(const std::string& name) const;
    void addAppender(std::unique_ptr<ILogAppender> appender);
    void removeAppender(const std::string& name);

private:

    struct ConfigInternal
    {
        ConfigInternal();
        explicit ConfigInternal(LogLevel level);

        LogLevel    m_logLevel;
        std::vector<std::unique_ptr<ILogAppender> > m_appenders;
    };

    std::shared_ptr<ConfigInternal> m_configData;
};

template<class T>
T* LoggingConfig::getAppender(const std::string& name) const
{
    for (const auto& appender : m_configData->m_appenders)
    {
        if (appender->getName() == name)
        {
            return static_cast<T*>(appender.get());
        }
    }
    return nullptr;
}

OC_NS_END;