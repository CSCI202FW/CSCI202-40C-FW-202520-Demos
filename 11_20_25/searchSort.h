#ifndef SEARCH_H
#define SEARCH_H

#include <fstream>
#include "unorderedLinkedList.h"

template <class t>
linkedListIterator<t> seqSearch(unorderedLinkedList<t> &list, const t &item)
{
    bool found = false;
    linkedListIterator<t> itRet;
    for (linkedListIterator<t> it = list.begin(); it != list.end() && !found; ++it)
    {
        if (*it == item)
        {
            found = true;
            itRet = it;
        }
    }
    if (found)
    {
        return itRet;
    }
    else
    {
        return list.end();
    }
}

template <class t>
int binarySearch(const t list[], int length, const t &item, int &comp, int first, int last)
{
    if (last < first)
    {
        return -1;
    }
    int mid = 0;
    mid = (first + last) / 2;
    comp++;
    if (list[mid] == item)
    {
        return mid;
    }
    else if (list[mid] > item)
    {
        return binarySearch(list, length, item, comp, first, mid - 1);
    }
    else if (list[mid] < item)
    {
        return binarySearch(list, length, item, comp, mid + 1, last);
    }
    return -1;
}

// =========== Sort Algorithms ==============
template <class t>
void bubbleSort(unorderedLinkedList<t> &list)
{
    std::ofstream out("bubble.txt");
    for (int iteration = 1; iteration < list.length(); iteration++)
    {
        out << "bsort" << iteration << std::endl;
        for (linkedListIterator<t> it = list.begin(); (it + 1) != list.end(); ++it)
        {
            linkedListIterator<t> it1 = it + 1;
            if (*it > *it1)
            {
                swap(it, it1);
            }
        }
    }
}

template <class t>
void swap(linkedListIterator<t> &first, linkedListIterator<t> &second)
{
    t temp = *first;
    *first = *second;
    *second = temp;
}

template <class t>
linkedListIterator<t> findSmallest(unorderedLinkedList<t> list, linkedListIterator<t> &begin)
{
    t smallest = *begin;
    linkedListIterator<t> ret = begin;
    for (linkedListIterator<t> it = begin + 1; it != list.end(); ++it)
    {
        if (*it < smallest)
        {
            smallest = *it;
            ret = it;
        }
    }
    return ret;
}

template <class t>
void selectionSort(unorderedLinkedList<t> &list)
{
    linkedListIterator<t> unsort = list.begin();
    int i = 1;
    for (unsort; unsort != list.end(); ++unsort)
    {
        linkedListIterator<t> smallest = findSmallest(list, unsort);
        if (smallest != unsort)
        {
            swap(unsort, smallest);
        }
    }
}

template <class t>
void insertionSort(t list[], int length)
{
    for (int firstOutOfOrder = 1; firstOutOfOrder < length; ++firstOutOfOrder)
    {
        if (list[firstOutOfOrder] < list[firstOutOfOrder - 1])
        {
            t temp = list[firstOutOfOrder];
            int location = firstOutOfOrder;
            do
            {
                list[location] = list[location - 1];
                location--;
            } while (location > 0 && list[location - 1] > temp);
            list[location] = temp;
        }
    }
}

#endif