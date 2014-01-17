#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"

#include "core/common.h"
#include "core/assert.h"
#include "core/logging/logger.h"


TEST(LOGGING, InitLogging) 
{
    OC_LOG_INFO("ALLO log2 ");

    EXPECT_EQ(1, 1);
}