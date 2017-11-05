#include "graph.h"
#include <climits> //limits.h?

graph::graph()
{
    size = 0;
    mapping = new hashTable(0);
}

int graph::insert(const std::string &name)
{
    if (mapping->contains(name))
        return 1;
    node N = new node();
    N.d = INT_MAX;
    N.p = NULL;
    N.known = false;
    V.push_back(N);
    mapping->insert(name,);//need pointer here
    return 0;
}

void graph::getData()
{
    
}