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

TEST(LOGGING, InitLogging) 
{
    LoggingConfig config(LogLevel::Debug);

    config.addAppender(std::unique_ptr<ILogAppender>(new DebugConsoleAppender()));
    config.addAppender(std::unique_ptr<ILogAppender>(new StdOutAppender()));

    Logger::init(config);

    OC_LOG_DEBUG("ALLO");

    EXPECT_EQ(1, 1);
}