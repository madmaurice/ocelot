
#pragma once

OC_NS_BG;

struct StackFrame
{
    size_t m_depth;
    String m_function;
    String m_file;
    uint32 m_line;
};

std::ostream& operator<<(std::ostream& os, const StackFrame& frame);

typedef Vector<StackFrame> StackTrace;

class CallStack
{
public:

    CallStack();
    CallStack(const Vector<uint64>& addresses);

    void Append(uint64 address);
    void Remove(size_t position);

    size_t GetSize() const;

    StackTrace GetTrace() const;
    StackFrame GetFrame(size_t position) const;
    StackFrame operator[](size_t position) const;

    String ToString() const;

private:
    typedef std::shared_ptr<Vector<uint64>> StackPtr;
    StackPtr m_stack;
};

std::ostream& operator<<(std::ostream& os, const CallStack& callStack);

OC_NS_END;