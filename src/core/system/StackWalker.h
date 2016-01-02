
#pragma once
#include "callStack.h"

OC_NS_BG;

class StackWalkerImpl;

class StackWalker
{
public:
    static bool Init();
    static void Shutdown();

    static CallStack GetCallStack(uint32 maxDepth, uint32 startDepth = 0);

private:
    static std::unique_ptr<StackWalkerImpl> m_pImpl;
};

OC_NS_END;