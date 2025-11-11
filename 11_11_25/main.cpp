#include "arrayStack.h"

int main()
{
    arrayStack<int> myStack(20);
    myStack.push(7);
    myStack.push(12);
    arrayStack<int> yourStack = myStack;
    myStack.push(34);
    yourStack = myStack;
    return 0;
}