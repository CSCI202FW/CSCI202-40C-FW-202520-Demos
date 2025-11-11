#ifndef ASTACK_H
#define ASTACK_H
#include "stackADT.h"
#include <stdexcept>

template <class t>
class arrayStack : public stackADT<t>
{
public:
    const static int DEFAULT_STACK_SIZE = 100;
    arrayStack(int = DEFAULT_STACK_SIZE);
    arrayStack(const arrayStack<t> &);
    const arrayStack<t> &operator=(const arrayStack<t> &);
    void initializeStack();
    bool isFullStack() const;
    bool isEmptyStack() const;
    void push(const t &);
    t peek() const;
    t top() const;
    t pop();
    ~arrayStack();

private:
    void copyStack(const arrayStack<t> &);
    t getTopItem() const;
    int maxStackSize;
    int stackTop;
    t **list;
};

template <class t>
arrayStack<t>::arrayStack(int max)
{
    if (max <= 0)
    {
        max = DEFAULT_STACK_SIZE;
    }
    maxStackSize = max;
    stackTop = 0;
    list = new t *[maxStackSize];
    for (int i = 0; i < maxStackSize; i++)
    {
        list[i] = nullptr;
    }
}

template <class t>
arrayStack<t>::arrayStack(const arrayStack<t> &stackToCopy)
{
    stackTop = 0;
    list = nullptr;
    maxStackSize = 0;
    copyStack(stackToCopy);
}

template <class t>
const arrayStack<t> &arrayStack<t>::operator=(const arrayStack<t> &stackToCopy)
{
    if (this != &stackToCopy)
    {
        copyStack(stackToCopy);
    }
    return *this;
}

template <class t>
void arrayStack<t>::initializeStack()
{
    if (!isEmptyStack())
    {
        for (int i = 0; i < stackTop; i++)
        {
            delete list[i];
            list[i] = nullptr;
        }
    }
    stackTop = 0;
}

template <class t>
bool arrayStack<t>::isFullStack() const
{
    return stackTop == maxStackSize;
}

template <class t>
bool arrayStack<t>::isEmptyStack() const
{
    return stackTop == 0;
}

template <class t>
void arrayStack<t>::push(const t &newItem)
{
    if (!isFullStack())
    {
        list[stackTop] = new t(newItem);
        stackTop++;
    }
    else
    {
        throw std::overflow_error("Stack Overflow. Cannot add to a full stack.");
    }
}

template <class t>
t arrayStack<t>::peek() const
{
    return getTopItem();
}

template <class t>
t arrayStack<t>::top() const
{
    return getTopItem();
}

template <class t>
t arrayStack<t>::pop()
{
    if (isEmptyStack())
    {
        throw std::underflow_error("Stack underflow. Cannot remove from an empty stack.");
    }
    t copy = getTopItem();
    delete list[stackTop - 1];
    list[stackTop - 1] = nullptr;
    stackTop--;
    return copy;
}

template <class t>
arrayStack<t>::~arrayStack()
{
    initializeStack();
    delete[] list;
}

template <class t>
void arrayStack<t>::copyStack(const arrayStack<t> &stackToCopy)
{
    if (!isEmptyStack())
    {
        initializeStack();
    }
    if (this->maxStackSize != stackToCopy.maxStackSize)
    {
        delete[] this->list;
        this->maxStackSize = stackToCopy.maxStackSize;
        this->list = new t *[this->maxStackSize];
    }
    this->stackTop = stackToCopy.stackTop;
    for (int i = 0; i < this->stackTop; i++)
    {
        this->list[i] = new t(*(stackToCopy.list[i]));
    }
}

template <class t>
t arrayStack<t>::getTopItem() const
{
    if (isEmptyStack())
    {
        throw std::out_of_range("Empty Stack");
    }
    return *(list[stackTop - 1]);
}

#endif