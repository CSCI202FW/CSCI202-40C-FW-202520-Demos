#ifndef PQUEUE_H
#define PQUEUE_H

#include "linkedQueue.h"
template <class t>
class fakePriorityQueue : public linkedQueue<t>
{
public:
    void enqueue(const t &);
};
template <class t>
void fakePriorityQueue<t>::enqueue(const t &queueElement)
{
    // modify to put items in order by priority.
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(queueElement);
    newNode->link = nullptr;
    if (this->isEmptyQueue())
    {
        this->queueFront = newNode;
        this->queueRear = newNode;
    }
    else
    {
        this->queueRear->link = newNode;
        this->queueRear = newNode;
    }
}

#endif