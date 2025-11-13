#include "arrayQueue.h"
#include <fstream>

int main()
{

    std::ifstream fin("input.txt");
    arrayQueue<int> myQueue(1000000);
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
    }
    for (int i = 0; i < 1000000; i++)
    {
        myQueue.dequeue();
        if (fin.eof())
        {
            fin.seekg(0);
        }
        fin >> x;
        myQueue.enqueue(x);
    }

    return 0;
}