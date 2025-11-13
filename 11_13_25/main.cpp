#include "arrayQueue.h"
#include "linkedQueue.h"
#include <fstream>

// m03 part b lab adjust the enqueue in fake priority queue to be ordered
// make sure to preserve FIFO for items that are the equal

int main()
{

    std::ifstream fin("input.txt");
    arrayQueue<int> myQueue(1000000);
    linkedQueue<int> lQueue;
    int x;
    /* fin >> x;
    myQueue.enqueue(x);
    fin >> x;
    myQueue.enqueue(x);
    fin >> x;
    myQueue.enqueue(x); */
    for (int i = 0; i < 999999; i++)
    {
        // myQueue.dequeue();
        if (fin.eof())
        {
            fin.seekg(0);
        }
        fin >> x;
        myQueue.enqueue(x);
        lQueue.enqueue(x);
    }
    for (int i = 0; i < 1000000; i++)
    {
        myQueue.dequeue();
        lQueue.dequeue();
        if (fin.eof())
        {
            fin.seekg(0);
        }
        fin >> x;
        myQueue.enqueue(x);
        lQueue.enqueue(x);
    }

    return 0;
}