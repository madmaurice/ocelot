
#include "gtest/gtest.h"
#include "core/system/StackWalker.h"
#include <iostream>
#include "core/util/NonCopyable.h"

using namespace OC;

class StackWalkFixture : public ::testing::Test
{
public:

protected:
    virtual void SetUp()
    {
        StackWalker::Init();
    }

    virtual void TearDown()
    {
        StackWalker::Shutdown();
    }
};


typedef StackWalkFixture STACK_WALK;

TEST_F(STACK_WALK, GetStackTrace) 
{
    CallStack stack = StackWalker::GetCallStack(50);
    std::cout << "STACK" << std::endl;
    std::cout << stack << std::endl;

    std::cout << "FRAME 4" << std::endl;
    StackFrame frame = stack.GetFrame(4);
    std::cout << frame << std::endl;
}