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

    LogLevel getLogLevel();
    void setLogLevel(LogLevel level);


    std::vector<std::unique_ptr<ILogAppender> >& getAllAppenders();
    ILogAppender* getAppender(std::string name);
    void addAppender(std::unique_ptr<ILogAppender> appender);
    void removeAppender(std::string name);

    //setCategories(Vector<LogCategory>)
    //setCategories<T>(LogCategoryPolicy : T)
    //enableCategory(uint32) : void
    //disableCategory(uint32) : void
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

OC_NS_END;