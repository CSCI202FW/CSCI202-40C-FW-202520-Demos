#include "donut.h"
#include "linkedList.h"

int main()
{
    linkedListType<int> myList;
    int x = 7;
    x = x;
    myList = myList;
    linkedListType<int> yourList = myList;

    return 0;
}