#include "graph.h"
#include <iostream>
#include <fstream>

// M06 part b lab
//  fill in the connected function in the graph class.
//  the function returns true if two vertexes are connected
//  it will return false if they are not.

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
    std::cout << g.breadthFirstTraversal() << std::endl;
    return 0;
}