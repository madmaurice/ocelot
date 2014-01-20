#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"

#include "core/common.h"
#include "core/assert.h"
#include "core/logging/logger.h"
#include "core/logging/loggingConfig.h"

using namespace oc;


TEST(LOGGING, DISABLED_InitLogging) 
{
    LoggingConfig config(LogLevel::Debug);

    config.addAppender(oc::make_unique<DebugConsoleAppender>());
    config.addAppender(oc::make_unique<StdOutAppender>());

    Logger::init(config);

    OC_LOG_DEBUG("ALLO");

    EXPECT_EQ(1, 1);
}

TEST(LOGGING, LogFormatter) 
{
    LoggingConfig config(LogLevel::Debug);

    //std::shared_ptr<TimeFormatter> formatter(std::make_shared<TimeFormatter>(new LogFormatter()));
    std::shared_ptr<TimeFormatter> formatter(new TimeFormatter(new LogFormatter()));

    TimeFormatter formatter2(new LogFormatter);
    formatter2 = *formatter;

    //config.addAppender(oc::make_unique<DebugConsoleAppender>());
    config.addAppender(oc::make_unique<StdOutAppender>(formatter));

    Logger::init(config);

    OC_LOG_DEBUG("ALLO");

    EXPECT_EQ(1, 1);
}

TEST(LOGGING, DISABLED_CopyLogFormatter) 
{
    LoggingConfig config(LogLevel::Debug);

    std::shared_ptr<TimeFormatter> formatter(new TimeFormatter(new LogFormatter()));
    config.addAppender(oc::make_unique<StdOutAppender>(formatter));

    Logger::init(config);

    OC_LOG_DEBUG("ALLO");

    EXPECT_EQ(1, 1);
}