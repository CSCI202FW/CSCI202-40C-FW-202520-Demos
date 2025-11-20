#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "unorderedLinkedList.h"
#include "searchSort.h"
#include "person.h"

int compareByName(Person *&, Person *&);
int compareByAge(Person *&, Person *&);
int compareByHeight(Person *&, Person *&);

// M04 part b lab. which sort do you prefer and why?

int main()
{
    Person **people = new Person *[10];
    people[0] = new Person("Brian Busch", 32, 168);
    people[1] = new Person("Amber Hammond", 49, 155);
    people[2] = new Person("Jason Buckles", 28, 182);
    people[3] = new Person("Richard Asbury", 42, 182);
    people[4] = new Person("Rebecca Rivera", 69, 174);
    people[5] = new Person("Nikia Shurtleff", 51, 163);
    people[6] = new Person("Derek Hancock", 29, 168);
    people[7] = new Person("Elias Gomez", 47, 184);
    people[8] = new Person("Timothy Michael", 49, 170);
    people[9] = new Person("Bernard McElroy", 60, 183);
    quickSort(people, 0, 9, compareByAge);
    for (int i = 0; i < 10; i++)
    {
        std::cout << *people[i] << std::endl;
    }
    quickSort(people, 0, 9, compareByName);
    for (int i = 0; i < 10; i++)
    {
        std::cout << *people[i] << std::endl;
    }
    quickSort(people, 0, 9, compareByHeight);
    for (int i = 0; i < 10; i++)
    {
        std::cout << *people[i] << std::endl;
    }
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
    // insertionSort(ilist, 1000000);
    // sList.insertionSort();
    mergeSort(ilist, 0, 1000000);
    sList.mergeSort();
    std::cout
        << "Merge Sort Finished!" << std::endl;

    return 0;
}

int compareByName(Person *&person1, Person *&person2)
{
    if (person1->getName() > person2->getName())
    {
        return 1;
    }
    if (person1->getName() == person2->getName())
    {
        return 0;
    }
    if (person1->getName() < person2->getName())
    {
        return -1;
    }
    return 0;
}

int compareByAge(Person *&person1, Person *&person2)
{
    if (person1->getAge() > person2->getAge())
    {
        return 1;
    }
    if (person1->getAge() == person2->getAge())
    {
        return 0;
    }
    if (person1->getAge() < person2->getAge())
    {
        return -1;
    }
    return 0;
}

int compareByHeight(Person *&person1, Person *&person2)
{
    if (person1->getHeight() > person2->getHeight())
    {
        return 1;
    }
    if (person1->getHeight() == person2->getHeight())
    {
        return 0;
    }
    if (person1->getHeight() < person2->getHeight())
    {
        return -1;
    }
    return 0;
}
