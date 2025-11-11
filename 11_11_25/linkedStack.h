#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "stackADT.h"
#include "node.h"
#include <stdexcept>

template <class t>
class linkedStack : public stackADT<t>
{
public:
    linkedStack(int = 100);
    linkedStack(const linkedStack<t> &);
    const linkedStack<t> &operator=(const linkedStack<t> &);
    void initializeStack();
    bool isFullStack() const;
    bool isEmptyStack() const;
    void push(const t &);
    t peek() const;
    t top() const;
    t pop();
    ~linkedStack();

private:
    void copyStack(const linkedStack<t> &);
    t getTopItem() const;
    node<t> *stackTop;
    int count;
};

template <class t>
linkedStack<t>::linkedStack(int)
{
    stackTop = nullptr;
}

template <class t>
linkedStack<t>::~linkedStack()
{
    initializeStack();
}

template <class t>
t linkedStack<t>::getTopItem() const
{
    if (isEmptyStack())
    {
        throw std::out_of_range("Empty Stack")
    }
    return *(stackTop->data);
}

template <class t>
void linkedStack<t>::initializeStack()
{
    node<t> *temp;
    while (stackTop != nullptr)
    {
        temp = stackTop;
        stackTop = stackTop->link;
        delete temp;
    }
    count = 0;
}

template <class t>
bool linkedStack<t>::isFullStack() const
{
    return false;
}

template <class t>
bool linkedStack<t>::isEmptyStack() const
{
    return stackTop == nullptr;
}
template <class t>
t linkedStack<t>::peek() const
{
    return getTopItem();
}
template <class t>
t linkedStack<t>::top() const
{
    return getTopItem();
}
#endif