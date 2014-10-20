
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

typedef std::vector<StackFrame> StackTrace;

class CallStack
{
public:

    CallStack();
    CallStack(const std::vector<uint64>& addresses);

    void append(uint64 address);
    void remove(size_t position);

    size_t getSize() const;

    StackTrace getTrace() const;
    StackFrame getFrame(size_t position) const;
    StackFrame operator[](size_t position) const;

    String toString() const;

private:
    typedef std::shared_ptr<std::vector<uint64>> StackPtr;
    StackPtr m_stack;
};

std::ostream& operator<<(std::ostream& os, const CallStack& callStack);

OC_NS_END;