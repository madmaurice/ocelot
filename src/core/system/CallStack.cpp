
#include "CallStack.h"
#include <windows.h>

#pragma warning(push)
#pragma warning(disable: 4091)
#include <DbgHelp.h>
#pragma warning(pop)

OC_NS_BG;

namespace
{
    StackFrame AddressToStackFrame(uint64 address)
    {
        StackFrame frame;
        const HANDLE processHandle = GetCurrentProcess();
        DWORD64 displacement = 0;

        // Init symbol
        uint64 buffer[ (sizeof(SYMBOL_INFO) + 1024 + sizeof(ULONG64) - 1) / sizeof(ULONG64) ] = { 0 };
        SYMBOL_INFO *info = (SYMBOL_INFO *)buffer;
        info->SizeOfStruct = sizeof(SYMBOL_INFO);
        info->MaxNameLen = 1024;

        // Attempt to get information about the symbol to create the StackFrame
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

CallStack::CallStack(const Vector<uint64>& addresses )
    : m_stack(std::make_shared<Vector<uint64>>(addresses))
{
}

void CallStack::Append(uint64 address)
{
    m_stack->push_back(address);
}

void CallStack::Remove(size_t position)
{
    OC_ASSERT(position <= m_stack->size());
    m_stack->erase(m_stack->begin() + position);
}

size_t CallStack::GetSize() const
{
    return m_stack->size();
}

StackTrace CallStack::GetTrace() const
{
    StackTrace trace;
    int i = 0;
    for (const auto& address : *m_stack)
    {
        StackFrame frame = AddressToStackFrame(address);
        frame.m_depth = i++;
        trace.push_back(frame);
    }
    return trace;
}

StackFrame CallStack::GetFrame(size_t position) const
{
    OC_ASSERT(position <= m_stack->size());
    StackFrame frame = AddressToStackFrame((*m_stack)[position]);
    frame.m_depth = position;
    return frame;
}

StackFrame CallStack::operator[](size_t position) const
{
    return GetFrame(position);
}

String CallStack::ToString() const
{
    std::stringstream sstream;
    DWORD64 displacement = 0;

    const HANDLE processHandle = GetCurrentProcess();
    for (const auto& address : *m_stack)
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
    os << stackTrace.ToString();
    return os;
}

OC_NS_END;