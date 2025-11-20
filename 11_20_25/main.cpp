#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "unorderedLinkedList.h"
#include "searchSort.h"

int main()
{
    unorderedLinkedList<int> list;
    unorderedLinkedList<int> blist;
    unorderedLinkedList<int> sList;
    int ilist[1000000];
    std::ifstream in("input.txt");
    int i = 0;
    while (!in.eof())
    {
        int x;
        in >> x;
        list.insert(x);
        ilist[i++] = x;
    }
    blist = list;
    sList = list;
    int searchTerm = 9357854;
    linkedListIterator<int> it = seqSearch(list, searchTerm);
    if (it == list.end())
    {
        std::cout << "The item was not found in the list" << std::endl;
    }
    else
    {
        std::cout << *it << " is in the list" << std::endl;
    }
    // bubbleSort(blist);
    // std::cout << "Bubble Sort Finished!" << std::endl;
    insertionSort(ilist, 1000000);
    std::cout << "Insertin Sort Finished!" << std::endl;

    return 0;
}