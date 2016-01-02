
#include "StackWalker.h"
#include <windows.h>
#include <DbgHelp.h>
#include <sstream>

OC_NS_BG;

class StackWalkerImpl
{
public:

    bool Init();
    void Shutdown();

    CallStack GenerateCallStack(uint32 maxDepth, uint32 startDepth);
private:
    static const uint32 MAX_DEPTH = 20;
};

bool StackWalkerImpl::Init()
{
    // Init symbols
    uint32 symOpts = SymGetOptions();

    symOpts |= SYMOPT_LOAD_LINES;
    symOpts |= SYMOPT_FAIL_CRITICAL_ERRORS;
    symOpts |= SYMOPT_DEFERRED_LOADS;
    symOpts |= SYMOPT_EXACT_SYMBOLS;

    //This symbol option causes public symbol names to be undecorated when they are displayed, 
    //and causes searches for symbol names to ignore symbol decorations. 
    // Private symbol names are never decorated, regardless of whether this option is active. 
    //For information on symbol name decorations, see : http://msdn.microsoft.com/en-us/library/windows/hardware/ff553493(v=vs.85).aspx
    symOpts |= SYMOPT_UNDNAME;

    SymSetOptions(symOpts);

    if (!SymInitialize(GetCurrentProcess(), NULL, TRUE))
    {
        OC_LOG_ERROR("SymInitialize returned false");
        return false;
    }

    // Load modules?
    return true;
}

void StackWalkerImpl::Shutdown()
{
    SymCleanup(GetCurrentProcess());
}

CallStack StackWalkerImpl::GenerateCallStack(uint32 maxDepth, uint32 startDepth)
{
    startDepth += 1; // Increment to remove the getCallStack call
    const uint32 depth = maxDepth > 0 ? maxDepth : MAX_DEPTH;

    std::vector<uint64> backTrace;
    backTrace.resize(depth, 0);

    uint32 machineType = IMAGE_FILE_MACHINE_I386;

    // Get context, process and thread information.
    CONTEXT context;
    RtlCaptureContext(&context);
    const HANDLE processHandle = GetCurrentProcess();
    const HANDLE threadHandle = GetCurrentThread();

    STACKFRAME64 stackFrame64;
    memset(&stackFrame64, 0, sizeof(stackFrame64));

    stackFrame64.AddrPC.Mode         = AddrModeFlat;
    stackFrame64.AddrStack.Mode      = AddrModeFlat;
    stackFrame64.AddrFrame.Mode      = AddrModeFlat;
#if _WIN64
    stackFrame64.AddrPC.Offset       = context.Rip;
    stackFrame64.AddrStack.Offset    = context.Rsp;
    stackFrame64.AddrFrame.Offset    = context.Rbp;
    machineType                      = IMAGE_FILE_MACHINE_AMD64;
#else	// _WIN64
    stackFrame64.AddrPC.Offset       = context.Eip;
    stackFrame64.AddrStack.Offset    = context.Esp;
    stackFrame64.AddrFrame.Offset    = context.Ebp;
#endif	// _WIN64

    // Walk the stack one frame at a time
    bool stackWalkSucceeded	= true;
    for (uint32 currentDepth = 0; stackWalkSucceeded && (currentDepth < depth); ++currentDepth)
    {
        stackWalkSucceeded = !!StackWalk64(machineType, processHandle, threadHandle, 
            &stackFrame64, &context, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL);

        // Skip start of stack
        if (currentDepth >= startDepth)
        {
            backTrace[currentDepth] = stackFrame64.AddrPC.Offset;
        }

        if(!stackWalkSucceeded)
        {
            // Give up
            DWORD lastError = GetLastError();
            OC_LOG_ERROR("StackWalk64 failed, error : " << lastError);
            break;
        }

        // Stop if the frame pointer or address is NULL.
        if(stackFrame64.AddrFrame.Offset == 0 || stackFrame64.AddrPC.Offset == 0) 
        {
            break;
        }
    }

    return CallStack(backTrace);
}

//---------- StackWalker ----------//
std::unique_ptr<StackWalkerImpl> StackWalker::m_pImpl = nullptr;

CallStack StackWalker::GetCallStack(uint32 maxDepth, uint32 startDepth)
{
    OC_ASSERT_MSG(m_pImpl.get() != nullptr, "StackWalker not initialized");
    return m_pImpl->GenerateCallStack(maxDepth, startDepth);
}

bool StackWalker::Init()
{
    OC_ASSERT_MSG(m_pImpl.get() == nullptr, "StackWalker already initialized");
    m_pImpl.reset(new StackWalkerImpl());

    return m_pImpl->Init();
}

void StackWalker::Shutdown()
{
    OC_ASSERT_MSG(m_pImpl.get() != nullptr, "StackWalker not initialized");
    m_pImpl->Shutdown();

    m_pImpl.reset(nullptr);
}

OC_NS_END;