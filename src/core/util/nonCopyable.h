
#pragma once

/*
Potential "issue" :

struct A : NonCopyable {};
struct B : NonCopyable {};
struct C : A, B {};

In this case C inherits two sub-objects of the same base class NonCopyable. 
The standard requires sub-objects of the same base class to have distinct addresses, which prohibits empty base class optimization in this case and make the sizeof(C) at least 2.

To make empty base class optimization work something like the following can be done:

template<class Tag>
class NonCopyable { ... };
struct A : NonCopyable<A> {};
struct B : NonCopyable<B> {};
struct C : A, B {};

Here, C does not have any base class sub-objects of the same type, which allows for empty base class optimization.
*/

class NonCopyable
{
protected:
    NonCopyable() {}
    ~NonCopyable() {} /// Protected non-virtual destructor
private: 
    NonCopyable(const NonCopyable &);
    NonCopyable& operator =(const NonCopyable &);
};  