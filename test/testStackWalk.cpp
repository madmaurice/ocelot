
#include "gtest/gtest.h"
#include "core/system/stackWalker.h"
#include <iostream>
#include "core/util/nonCopyable.h"

using namespace oc;

class StackWalkFixture : public ::testing::Test
{
public:

protected:
    virtual void SetUp()
    {
        StackWalker::init();
    }

    virtual void TearDown()
    {
        StackWalker::shutdown();
    }
};


typedef StackWalkFixture STACK_WALK;

TEST_F(STACK_WALK, GetStackTrace) 
{
    CallStack stack = StackWalker::getCallStack(50);
    std::cout << stack << std::endl;

    StackFrame frame = stack.getFrame(2);
    std::cout << frame << std::endl;
}