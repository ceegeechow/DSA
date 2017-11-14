#include "graph.h"
#include "heap.h"
#include <stdio.h>

void graph::insert(const string &name1, const string &name2, int c)
{
    //add vertices that don't already exist in graph
    if (!mapping->contains(name1))
    {
        node n;
        n.name = name1;
        V.push_back(n);
        mapping->insert(name1, &V.back());
    }
    if (!mapping->contains(name2))
    {
        node n;
        n.name = name2;
        V.push_back(n);
        mapping->insert(name2, &V.back());
    }
    //add edge with destination name2 and cost c
    node *p1 = static_cast<node *> (mapping->getPointer(name1));
    node *p2 = static_cast<node *> (mapping->getPointer(name2));
    edge e;
    e.dest = p2;
    e.cost = c;
    p1->adj.push_back(e);
}

void graph::dijkstra(const string &s)
{
    heap H = heap(V.size());
    node *ps = static_cast<node *> (mapping->getPointer(s));
    ps->d = 0;
    for (node n : V)
    {
       H.insert(n.name, n.d, &n);
    }
    node* pv;
    while (H.deleteMin(NULL, NULL, &pv) == 0)
    {
        pv->known = true;
        for (edge e : pv->adj)
        {
            node* pw = e.dest;
            if (!(pw->known) && (pv->d + e.cost < pw->d))
            {
                pw->d = pv->d + e.cost;
                H.setKey(pw->name, pw->d);
                pw->p = pv;
            }
        }
    }
}

int graph::output(const string fname)
{
//    FILE* outFile = fopen(fname,"w");
//    if (outFile == NULL)
//    {
//        fprintf(stderr, "Error openning output file '%s'\n", fname);
//        return -1;
//    }
//    
//    fclose(outFile);
    return 0;
}

int main() {
    return 0;
}