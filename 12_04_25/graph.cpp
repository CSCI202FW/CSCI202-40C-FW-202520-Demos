#include "graph.h"
// graph viz online https://dreampuf.github.io/GraphvizOnline/

graphType::graphType(int size)
{
    if (size >= 0)
    {
        maxSize = size;
    }
    else
    {
        maxSize = 0;
    }
    if (maxSize > 0)
    {
        graph.resize(maxSize);
    }
}

graphType::graphType(const graphType &othGraph)
{
    maxSize = 0;
    copyGraph(othGraph);
}

graphType::~graphType()
{
    clearGraph();
}

const graphType &graphType::operator=(const graphType &otherGraph)
{
    if (this != &otherGraph)
    {
        copyGraph(otherGraph);
    }
    return *this;
}

bool graphType::isEmpty() const
{
    return graph.empty();
}

void graphType::createGraph(std::string filename)
{
    std::ifstream fin(filename);
    int index = 0;
    int vertex = 0;
    int adjcentVertex = 0;
    if (!isEmpty())
    {
        clearGraph();
    }
    if (!fin.is_open())
    {
        throw std::runtime_error("Cannot open input file");
    }
    int gSize = 0;
    fin >> gSize;
    if (gSize > maxSize)
    {
        maxSize = gSize;
        graph.resize(maxSize);
    }
    for (index = 0; index < gSize; index++)
    {
        fin >> vertex;
        fin >> adjcentVertex;
        while (adjcentVertex != -999)
        {
            graph[vertex].insert(adjcentVertex);
            fin >> adjcentVertex;
        }
    }
    fin.close();
}

void graphType::clearGraph()
{
    for (int i = 0; i < graph.size(); i++)
    {
        graph[i].destroyList();
    }
    graph.clear();
    maxSize = 0;
}

std::string graphType::printGraph()
{
    std::ostringstream out;
    out << "digraph {" << std::endl; // graphviz output
    for (int i = 0; i < graph.size(); i++)
    {
        /* out << i << " "; //python output
        graph[i].print(out); //python output
        out << std::endl; //python output */
        for (linkedListIterator<int> graphit = graph[i].begin(); graphit != graph[i].end(); ++graphit)
        {
            out << i << "->" << *graphit << ";" << std::endl;
        }
    }
    out << std::endl; // graph viz output
    out << "}";

    return out.str();
}

std::string graphType::depthFirstTraversal()
{
    bool *visited;
    visited = new bool[graph.size()];
    std::string output = "";
    for (int i = 0; i < graph.size(); i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < graph.size(); i++)
    {
        if (!visited[i])
        {
            dft(i, visited, output);
        }
    }
    delete[] visited;
    return output;
}

std::string graphType::dftAtVertex(int vertex)
{
    bool *visited;
    visited = new bool[graph.size()];
    std::string output = "";
    for (int i = 0; i < graph.size(); i++)
    {
        visited[i] = false;
    }
    dft(vertex, visited, output);
    delete[] visited;
    return output;
}

void graphType::copyGraph(const graphType &otherGraph)
{
    if (!this->isEmpty())
    {
        this->clearGraph();
    }
    this->maxSize = otherGraph.maxSize;
    graph.resize(this->maxSize);
    for (int i = 0; i < otherGraph.graph.size(); i++)
    {
        this->graph[i] = otherGraph.graph[i];
    }
}

void graphType::dft(int v, bool visited[], std::string &output)
{
    visited[v] = true;
    output = output + " " + std::to_string(v) + " ";
    linkedListIterator<int> graphIt;
    for (graphIt = graph[v].begin(); graphIt != graph[v].end(); ++graphIt)
    {
        int w = *graphIt;
        if (!visited[w])
        {
            dft(w, visited, output);
        }
    }
}
