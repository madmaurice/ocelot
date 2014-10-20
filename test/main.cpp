
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"
#include <windows.h>
#include <DbgHelp.h>
#include "core/system/types.h"


int main (int argc, char** argv)
{
    //Configure debugging stuff
    OC_DBG_CONFIG();

    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    return 0;
}