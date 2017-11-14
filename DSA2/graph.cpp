#include "graph.h"
#include "heap.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

void graph::insert(const string &name1, const string &name2, int c)
{
    //add nodes if they don't already exist in graph
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
    heap H = heap(V.size()); //heap to store unknown nodes
    node *ps = static_cast<node *> (mapping->getPointer(s)); //pointer to starting node
    ps->d = 0;
    //all nodes begin as unknown
    for (node n : V)
       H.insert(n.name, n.d, &n);

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
    list<string> path;
    node* currNode;
    //open output file
    ofstream fout;
    fout.open(fname);
    if (fout.fail())
    {
        cerr << "Error opening output file " << fname << "\n";
        return -1;
    }
    //print path to each node
    for (node n : V)
    {
        fout << n.name << ": ";
        if (n.d == INT_MAX)
        {
            fout << "NO PATH\n";
            continue;
        }
        else
        {
            fout << n.d << " [";
            currNode = &n;
            //store names of nodes in order in list
            do
            {
                path.push_front(currNode->name);
                currNode = currNode->p;
            } while (currNode != NULL);
            //print names to output file
            for (string name : path)
            {
                fout << name;
                if (name == *path.end())
                    break;
                fout << ", ";
            }
        }
        fout << "]\n";
        path.clear(); //efficient??
    }
    fout.close();
    return 0;
}