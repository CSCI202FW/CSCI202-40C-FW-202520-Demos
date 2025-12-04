#include "graph.h"
#include <iostream>
#include <fstream>

int main()
{
    graphType g;
    g.createGraph("graph.txt");
    std::cout << g.printGraph() << std::endl;
    std::ofstream fout("g.txt");
    fout << g.printGraph();
    std::cout << g.depthFirstTraversal() << std::endl
              << std::endl
              << std::endl;
    std::cout << g.dftAtVertex(0) << std::endl;
    return 0;
}