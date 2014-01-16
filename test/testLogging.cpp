#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"

#include "core/common.h"
#include "core/logging/logger.h"


TEST(LOGGING, InitLogging) 
{
    OC_LOG_INFO("ALLO");

    EXPECT_EQ(1, 1);
}