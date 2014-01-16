
#pragma once

#include "core/common.h"
#include "core/logging/logLevel.h"

OC_NS_BG;

class LoggingConfig
{
public:
    LoggingConfig();
    ~LoggingConfig();

    LogLevel getLogLevel();
    void setLogLevel(LogLevel level);

    //void setLogFormatter(const ILogFormatter& formatter)

    //getAllAppenders() : Vector<ILogAppender>
    //getAppenders(name : string) : ILogAppender
    //addAppender(unique_ptr<ILogAppender>)

    //setCategories(Vector<LogCategory>)
    //setCategories<T>(LogCategoryPolicy : T)
    //enableCategory(uint32) : void
    //disableCategory(uint32) : void
private:
    LogLevel    m_logLevel;
};

OC_NS_END;