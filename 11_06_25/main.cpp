#include "donut.h"
#include "unorderedLinkedList.h"

int main()
{
    unorderedLinkedList<int> myList;
    myList.insert(7);
    myList.insert(2);
    myList.insert(8);
    myList.print(std::cout, "...");
    unorderedLinkedList<Donut> donuts;
    donuts.insert(Donut("Maple", "M&Ms", "special"));
    donuts.print(std::cout, "\n");
    // int x = 7;
    // x = x;
    // myList = myList;
    //<int> yourList = myList;

    return 0;
}