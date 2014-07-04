
#include "callStack.h"
#include <windows.h>
#include <DbgHelp.h>

namespace
{
    StackFrame addressToStackFrame(uint64 address)
    {
        StackFrame frame;
        const HANDLE processHandle = GetCurrentProcess();
        DWORD64 displacement = 0;

        // Init symbol
        uint64 buffer[ (sizeof(SYMBOL_INFO) + 1024 + sizeof(ULONG64) - 1) / sizeof(ULONG64) ] = { 0 };
        SYMBOL_INFO *info = (SYMBOL_INFO *)buffer;
        info->SizeOfStruct = sizeof(SYMBOL_INFO);
        info->MaxNameLen = 1024;

        // Attempt to get information about the symbol and add it to the StackTrace
        if (SymFromAddr(processHandle, address, &displacement, info)) 
        {
            frame.m_function = String(info->Name, info->NameLen);

            // Get line number
            IMAGEHLP_LINE64	line;
            DWORD lineDisplacement = 0;
            if (SymGetLineFromAddr64(processHandle, address, &lineDisplacement, &line))
            {
                frame.m_file = line.FileName;
                frame.m_line = line.LineNumber;
            }
        }

        return frame;
    }
}

CallStack::CallStack()
{
}

CallStack::CallStack(const std::vector<uint64>& addresses )
    : m_stack(addresses)
{
}

void CallStack::append(uint64 address)
{
    m_stack.push_back(address);
}

void CallStack::remove(uint32 position)
{
    OC_ASSERT(position <= m_stack.size());
    m_stack.erase(m_stack.begin() + position);
}

size_t CallStack::getSize() const
{
    return m_stack.size();
}

StackTrace CallStack::getTrace() const
{
    StackTrace trace;
    int i = 0;
    for (const auto& address : m_stack)
    {
        StackFrame frame = addressToStackFrame(address);
        frame.m_depth = i++;
        trace.push_back(frame);
    }
    return trace;
}

StackFrame CallStack::getFrame(size_t position) const
{
    OC_ASSERT(position <= m_stack.size());
    StackFrame frame = addressToStackFrame(m_stack[position]);
    frame.m_depth = position;
    return frame;
}

StackFrame CallStack::operator[](size_t position) const
{
    return getFrame(position);
}

String CallStack::toString() const
{
    std::stringstream sstream;
    DWORD64 displacement = 0;

    const HANDLE processHandle = GetCurrentProcess();
    for (const auto& address : m_stack)
    {
        uint64 buffer[ (sizeof(SYMBOL_INFO) + 1024 + sizeof(ULONG64) - 1) / sizeof(ULONG64) ] = { 0 };
        SYMBOL_INFO *info = (SYMBOL_INFO *)buffer;
        info->SizeOfStruct = sizeof(SYMBOL_INFO);
        info->MaxNameLen = 1024;

        // Attempt to get information about the symbol and add it to the StackTrace
        if (SymFromAddr(processHandle, address, &displacement, info)) 
        {
            sstream << String(info->Name, info->NameLen);;

            // Get line number
            IMAGEHLP_LINE64	line;
            DWORD lineDisplacement = 0;
            if (SymGetLineFromAddr64(processHandle, address, &lineDisplacement, &line))
            {
                sstream << " (" << line.FileName << ":" << line.LineNumber << ")";
            }

            sstream << std::endl;
        }
    }

    return sstream.str();
}

std::ostream& operator<<(std::ostream& os, const StackFrame& frame)
{
    os << "[" << frame.m_depth << "] " << frame.m_function << " (" 
       << frame.m_file << ":" << frame.m_line << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const CallStack& stackTrace)
{
    os << stackTrace.toString();
    return os;
}
