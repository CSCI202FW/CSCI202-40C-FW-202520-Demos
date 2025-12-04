#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "unorderedLinkedList.h"

class graphType
{
public:
    graphType(int size = 0);
    graphType(const graphType &);
    ~graphType();
    const graphType &operator=(const graphType &);
    bool isEmpty() const;
    void createGraph(std::string);
    void clearGraph();
    std::string printGraph();
    std::string depthFirstTraversal();
    std::string dftAtVertex(int vertex);

protected:
    int maxSize;
    std::vector<unorderedLinkedList<int>> graph;

private:
    void copyGraph(const graphType &);
    void dft(int v, bool visited[], std::string &output);
};

#endif