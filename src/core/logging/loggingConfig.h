//---------------------------------------------------------------------------------------
//
// Logging configuration that is shared on copy
//
//---------------------------------------------------------------------------------------
#pragma once

#include "core/logging/logAppender.h"
#include "core/logging/logLevel.h"
#include "core/system/Containers.h"
#include <memory>

OC_NS_BG;

class LoggingConfig
{
public:
    LoggingConfig();
    explicit LoggingConfig(LogLevel defaultLogLevel);

    ~LoggingConfig();

    LogLevel GetLogLevel() const;
    void SetLogLevel(LogLevel level);

    const Vector<std::unique_ptr<ILogAppender> >& GetAllAppenders() const;

    template<class T>
    T* GetAppender(const String& name) const;
    void AddAppender(std::unique_ptr<ILogAppender> appender);
    void RemoveAppender(const String& name);

private:

    struct ConfigInternal
    {
        ConfigInternal();
        explicit ConfigInternal(LogLevel level);

        LogLevel    m_logLevel;
        Vector<std::unique_ptr<ILogAppender> > m_appenders;
    };

    std::shared_ptr<ConfigInternal> m_configData;
};

template<class T>
T* LoggingConfig::GetAppender(const String& name) const
{
    for (const auto& appender : m_configData->m_appenders)
    {
        if (appender->GetName() == name)
        {
            return static_cast<T*>(appender.get());
        }
    }
    return nullptr;
}

OC_NS_END;