#define BT_NO_SIMD_OPERATOR_OVERLOADS

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"
#include <windows.h>
#include <DbgHelp.h>
#include "core/system/types.h"

int32 CaptureStackTraceHelper(uint64* BackTrace, uint32 MaxDepth)
{
    STACKFRAME64		StackFrame64;
    HANDLE				ProcessHandle;
    HANDLE				ThreadHandle;
    unsigned long		LastError;
    bool				bStackWalkSucceeded	= true;
    uint32				CurrentDepth		= 0;
    uint32				MachineType			= IMAGE_FILE_MACHINE_I386;

    CONTEXT Context;
    RtlCaptureContext( &Context );

    CONTEXT				ContextCopy = Context;

#if !PLATFORM_SEH_EXCEPTIONS_DISABLED
    __try
#endif
    {
        // Get context, process and thread information.
        ProcessHandle	= GetCurrentProcess();
        ThreadHandle	= GetCurrentThread();

        // Zero out stack frame.
        memset( &StackFrame64, 0, sizeof(StackFrame64) );

        // Initialize the STACKFRAME structure.
        StackFrame64.AddrPC.Mode         = AddrModeFlat;
        StackFrame64.AddrStack.Mode      = AddrModeFlat;
        StackFrame64.AddrFrame.Mode      = AddrModeFlat;
#if _WIN64
        StackFrame64.AddrPC.Offset       = Context->Rip;
        StackFrame64.AddrStack.Offset    = Context->Rsp;
        StackFrame64.AddrFrame.Offset    = Context->Rbp;
        MachineType                      = IMAGE_FILE_MACHINE_AMD64;
#else	// _WIN64
        StackFrame64.AddrPC.Offset       = Context.Eip;
        StackFrame64.AddrStack.Offset    = Context.Esp;
        StackFrame64.AddrFrame.Offset    = Context.Ebp;
#endif	// _WIN64

        // Walk the stack one frame at a time.
        while( bStackWalkSucceeded && (CurrentDepth < MaxDepth) )
        {
            bStackWalkSucceeded = !!StackWalk64(  MachineType, 
                ProcessHandle, 
                ThreadHandle, 
                &StackFrame64,
                &ContextCopy,
                NULL,
                SymFunctionTableAccess64,
                SymGetModuleBase64,
                NULL );

            BackTrace[CurrentDepth++] = StackFrame64.AddrPC.Offset;

            if( !bStackWalkSucceeded  )
            {
                // StackWalk failed! give up.
                LastError = GetLastError( );
                break;
            }

            // Stop if the frame pointer or address is NULL.
            if( StackFrame64.AddrFrame.Offset == 0 || StackFrame64.AddrPC.Offset == 0 )
            {
                break;
            }
        }
    } 
#if !PLATFORM_SEH_EXCEPTIONS_DISABLED
    __except( EXCEPTION_EXECUTE_HANDLER )
    {
        // We need to catch any exceptions within this function so they don't get sent to 
        // the engine's error handler, hence causing an infinite loop.
        return EXCEPTION_EXECUTE_HANDLER;
    } 
#endif

    // NULL out remaining entries.
    for ( ; CurrentDepth<MaxDepth; CurrentDepth++ )
    {
        BackTrace[CurrentDepth] = NULL;
    }

    return EXCEPTION_EXECUTE_HANDLER;
}

bool GetStackWalk( std::string &outWalk )
{
    // Set up the symbol options so that we can gather information from the current
    // executable's PDB files, as well as the Microsoft symbol servers.  We also want
    // to undecorate the symbol names we're returned.  If you want, you can add other
    // symbol servers or paths via a semi-colon separated list in SymInitialized.
    ::SymSetOptions( SYMOPT_DEFERRED_LOADS | SYMOPT_INCLUDE_32BIT_MODULES | SYMOPT_UNDNAME );
    if (!::SymInitialize( ::GetCurrentProcess(), "http://msdl.microsoft.com/download/symbols", TRUE )) return false;

    // Capture up to 25 stack frames from the current call stack.  We're going to
    // skip the first stack frame returned because that's the GetStackWalk function
    // itself, which we don't care about.
    PVOID addrs[ 25 ] = { 0 };
    USHORT frames = CaptureStackBackTrace( 1, 25, addrs, NULL );

    for (USHORT i = 0; i < frames; i++) {
        // Allocate a buffer large enough to hold the symbol information on the stack and get 
        // a pointer to the buffer.  We also have to set the size of the symbol structure itself
        // and the number of bytes reserved for the name.
        ULONG64 buffer[ (sizeof( SYMBOL_INFO ) + 1024 + sizeof( ULONG64 ) - 1) / sizeof( ULONG64 ) ] = { 0 };
        SYMBOL_INFO *info = (SYMBOL_INFO *)buffer;
        info->SizeOfStruct = sizeof( SYMBOL_INFO );
        info->MaxNameLen = 1024;

        // Attempt to get information about the symbol and add it to our output parameter.
        DWORD64 displacement = 0;
        if (::SymFromAddr( ::GetCurrentProcess(), (DWORD64)addrs[ i ], &displacement, info )) {
            outWalk.append( info->Name, info->NameLen );
            outWalk.append( "\n" );
        }
    }

    ::SymCleanup( ::GetCurrentProcess() );

    return true;
}

void toto()
{
    std::cout << "toto" << std::endl;
    //std::string stack;
    //GetStackWalk(stack);
    uint64 bt[10];
    CaptureStackTraceHelper(bt, 10);
}

int main (int argc, char** argv)
{
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_WNDW);

    toto();

    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    return 0;
}