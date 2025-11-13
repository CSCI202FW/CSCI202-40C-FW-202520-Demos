#ifndef ARRAYQ_H
#define ARRAYQ_H
#include "queueADT.h"
#include <iostream>

template <class t>
class arrayQueue : public queueADT<t>
{
public:
    const static int DEFAULT_QUEUE_SIZE = 100;
    arrayQueue(int = DEFAULT_QUEUE_SIZE);
    arrayQueue(const arrayQueue<t> &);
    const arrayQueue<t> &operator=(const arrayQueue<t> &);
    ~arrayQueue();
    void enqueue(const t &queueElement);
    t dequeue();
    bool isEmptyQueue() const;
    bool isFullQueue() const;
    void initializeQueue();
    t front() const;
    t back() const;

private:
    t **list;
    int maxQueueSize;
    int queueFront;
    int queueRear;
    int count;
    void copyQueue(const arrayQueue<t> &);
};

template <class t>
arrayQueue<t>::arrayQueue(int max)
{
    if (max <= 0)
    {
        max = DEFAULT_QUEUE_SIZE;
    }
    maxQueueSize = max;
    list = new t *[maxQueueSize];
    for (int i = 0; i < maxQueueSize; i++)
    {
        this->list[i] = nullptr;
    }
    queueFront = maxQueueSize - 1;
    queueRear = maxQueueSize - 1;
    count = 0;
}
template <class t>
arrayQueue<t>::arrayQueue(const arrayQueue<t> &queueToCopy)
{
    this->list = nullptr;
    this->count = 0;
    this->queueFront = 0;
    this->queueRear = 0;
    copyQueue(queueToCopy);
}
template <class t>
const arrayQueue<t> &arrayQueue<t>::operator=(const arrayQueue<t> &queueToCopy)
{
    if (this != &queueToCopy) // no self copy
    {
        copyQueue(queueToCopy);
    }
    return *this;
}
template <class t>
arrayQueue<t>::~arrayQueue()
{
    initializeQueue();
    delete[] list;
    list = nullptr;
}
template <class t>
void arrayQueue<t>::enqueue(const t &queueElement)
{

    if (isFullQueue())
    {
        throw std::overflow_error("Cannot add to a full queue.");
    }
    /*  else if (queueRear == maxQueueSize)
     {
         std::cout << "Shifting elements" << std::endl;
         for (int i = queueFront; i > 0; i--)
         {
             for (int j = i; j < queueRear; j++)
             {
                 list[j - 1] = list[j];
             }
             queueRear--;
         }
         queueFront = 0;
     } */
    this->queueRear = (this->queueRear + 1) % maxQueueSize;
    list[queueRear] = new t(queueElement);
    count++;
}

template <class t>
t arrayQueue<t>::dequeue()
{
    if (isEmptyQueue())
    {
        throw std::out_of_range("Cannot delete an item in an empty queue.");
    }
    this->queueFront = (this->queueFront + 1) % maxQueueSize;
    t ret = *(list[this->queueFront]);
    delete list[this->queueFront];
    list[this->queueFront] = nullptr;
    count--;
    return ret;
}

template <class t>
bool arrayQueue<t>::isEmptyQueue() const
{

    return count == 0 || queueRear == queueFront;
}

template <class t>
bool arrayQueue<t>::isFullQueue() const
{

    return count == maxQueueSize || (queueRear + 1) % maxQueueSize == queueFront;
}

template <class t>
void arrayQueue<t>::initializeQueue()
{
    for (this->queueFront = (this->queueFront + 1) % maxQueueSize; !isEmptyQueue(); this->queueFront = (this->queueFront + 1) % maxQueueSize)
    {
        delete list[this->queueFront];
        list[this->queueFront] = nullptr;
    }
    this->queueFront = this->maxQueueSize - 1;
    this->queueRear = this->maxQueueSize - 1;
}

template <class t>
t arrayQueue<t>::front() const
{
    if (this->isEmptyQueue())
    {
        throw std::out_of_range("Cannot view an item in an empty queue.");
    }

    return *(list[(this->queueFront + 1) % maxQueueSize]);
}

template <class t>
t arrayQueue<t>::back() const
{
    if (this->isEmptyQueue())
    {
        throw std::out_of_range("Cannot view an item in an empty queue.");
    }
    return *(list[queueRear]);
}

template <class t>
void arrayQueue<t>::copyQueue(const arrayQueue<t> &queueToCopy)
{
    this->initializeQueue();
    delete[] this->list;
    this->maxQueueSize = queueToCopy.maxQueueSize;
    this->list = new t *[this->maxQueueSize];
    this->queueFront = queueToCopy.queueFront;
    this->queueRear = queueToCopy.queueRear;
    for (int i = (this->queueFront + 1) % maxQueueSize; i != queueRear; i = (i + 1) % maxQueueSize)
    {
        this->list[i] = new t(*(queueToCopy.list[i]));
    }
    this->list[this->queueRear] = new t(*(queueToCopy.list[queueToCopy.queueRear]));
}

#endif