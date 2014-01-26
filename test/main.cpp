#define BT_NO_SIMD_OPERATOR_OVERLOADS

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"

int main (int argc, char** argv)
{
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_WNDW);

    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    return 0;
}