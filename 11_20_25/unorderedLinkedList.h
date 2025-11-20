#ifndef UNORDERED_H
#define UNORDERED_H
#include "linkedList.h"

template <class t>
class unorderedLinkedList : public linkedListType<t>
{
public:
    enum directionType
    {
        FORWARD,
        BACKWARD
    };
    unorderedLinkedList(directionType = FORWARD);
    void insert(const t &newInfo);
    void deleteNode(const t &deleteItem);
    bool search(const t &searchItem) const;
    void insertionSort();
    void mergeSort();

private:
    directionType direction;
    void insertFirst(const t &newInfo);
    void insertLast(const t &newInfo);
    void recMergeSort(node<t> *&start);
    void divideList(node<t> *left, node<t> *&right);
    node<t> *mergeList(node<t> *left, node<t> *right);
};

template <class t>
unorderedLinkedList<t>::unorderedLinkedList(directionType d) : direction(d)
{
}

template <class t>
void unorderedLinkedList<t>::insert(const t &newInfo)
{
    if (direction == FORWARD)
    {
        insertLast(newInfo);
    }
    else
    {
        insertFirst(newInfo);
    }
}

template <class t>
void unorderedLinkedList<t>::deleteNode(const t &deleteItem)
{
    node<t> *current;
    node<t> *trailCurrent;
    bool found;
    if (this->isEmptyList())
    {
        throw std::out_of_range("Cannot delete from an empty list");
    }
    if (*(this->head->data) == deleteItem)
    {
        current = this->head;
        this->head = this->head->link;
        this->count--;
        if (this->head == nullptr)
        {
            this->tail = nullptr;
        }
        delete current;
    }
    else
    {
        found = false;
        trailCurrent = this->head;
        current = this->head->link;
        while (current != nullptr && !found)
        {
            if (*(current->data) != deleteItem)
            {
                trailCurrent = current;
                current = current->link;
            }
            else
            {
                found = true;
            }
        }

        if (found)
        {
            trailCurrent->link = current->link;
            this->count--;
            if (this->tail == current)
            {
                this->tail = trailCurrent;
            }
            delete current;
        }
        else
        {
            throw std::out_of_range("Item not found in list. Cannot delete.");
        }
    }
}

template <class t>
bool unorderedLinkedList<t>::search(const t &searchItem) const
{
    node<t> *current;
    bool found = false;
    current = this->head;
    while (current != nullptr && !found)
    {
        if (*(current->data) == searchItem)
        {
            found = true;
        }
        else
        {
            current = current->link;
        }
    }
    return found;
}

template <class t>
void unorderedLinkedList<t>::insertFirst(const t &newInfo)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newInfo);
    newNode->link = nullptr;
    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        newNode->link = this->head;
        this->head = newNode;
    }

    this->count++;
}

template <class t>
void unorderedLinkedList<t>::insertLast(const t &newInfo)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newInfo);
    newNode->link = nullptr;
    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        this->tail->link = newNode;
        this->tail = newNode;
    }

    this->count++;
}

template <class t>
void unorderedLinkedList<t>::insertionSort()
{
    node<t> *unsort;
    node<t> *prev;
    node<t> *current;
    node<t> *prevC;

    unsort = this->head->link;
    prev = this->head;
    while (unsort != nullptr)
    {
        if (*(unsort->data) < *(prev->data))
        {
            if (prev == this->head)
            {
                this->head->link = unsort->link;
                unsort->link = this->head;
                this->head = unsort;
            }
            else
            {
                current = this->head;
                while (current != unsort && *(current->data) < *(unsort->data))
                {
                    prevC = current;
                    current = current->link;
                }
                if (current == this->head)
                {
                    prev->link = unsort->link;
                    unsort->link = this->head;
                    this->head = unsort;
                }
                else
                {
                    prevC->link = unsort;
                    prev->link = unsort->link;
                    unsort->link = current;
                }
            }
        }
        else
        {
            prev = prev->link;
        }
        unsort = prev->link;
    }
    this->tail = prev;
}
template <class t>
void unorderedLinkedList<t>::mergeSort()
{
    recMergeSort(this->head);
    if (this->head == nullptr)
    {
        this->tail = nullptr;
    }
    else
    {
        this->tail = this->head;
        while (this->tail->link != nullptr)
        {
            this->tail = this->tail->link;
        }
    }
}
template <class t>
void unorderedLinkedList<t>::recMergeSort(node<t> *&start)
{
    node<t> *otherStart;
    if (start != nullptr)
    {
        if (start->link != nullptr)
        {
            divideList(start, otherStart);
            recMergeSort(start);
            recMergeSort(otherStart);
            start = mergeList(start, otherStart);
        }
    }
}
template <class t>
void unorderedLinkedList<t>::divideList(node<t> *left, node<t> *&right)
{
    node<t> *middle;
    node<t> *current;
    if (left == nullptr || left->link == nullptr)
    {
        right = nullptr;
    }
    else
    {
        middle = left;
        current = left->link;
        if (current != nullptr)
        {
            current = current->link;
        }
        while (current != nullptr)
        {
            middle = middle->link;
            current = current->link;
            if (current != nullptr)
            {
                current = current->link;
            }
        }
        right = middle->link;
        middle->link = nullptr;
    }
}
template <class t>
inline node<t> *unorderedLinkedList<t>::mergeList(node<t> *left, node<t> *right)
{
    node<t> *lastSmall;
    node<t> *newHead;
    if (left == nullptr)
        return right;
    if (right == nullptr)
        return left;
    if (*(left->data) <= *(right->data))
    {
        newHead = left;
        left = left->link;
    }
    else
    {
        newHead = right;
        right = right->link;
    }
    lastSmall = newHead;
    while (left != nullptr && right != nullptr)
    {
        if (*(left->data) <= *(right->data))
        {
            lastSmall->link = left;

            left = left->link;
        }
        else
        {
            lastSmall->link = right;
            right = right->link;
        }

        lastSmall = lastSmall->link;
    }
    if (left == nullptr)
    {
        lastSmall->link = right;
    }
    else
    {
        lastSmall->link = left;
    }
    return newHead;
}
#endif