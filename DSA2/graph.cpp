#include "graph.h"
#include "heap.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

graph::graph()
{
    mapping = new hashTable(100);
}

void graph::makeGraph()
{
    string filename;
    cout << "Enter name of input file: ";
    cin >> filename;
    ifstream fin(filename);
    if (fin.fail())
    {
        cerr << "Error opening input file " << filename << "\n";
        exit(1);
    }
    string v1, v2;
    int c;
    string line;
    while (getline(fin,line))
    {
        stringstream ss(line);
        ss >> v1 >> v2 >> c;
        insert(v1, v2, c);
    }
    fin.close();
}

void graph::insert(const string &name1, const string &name2, int c)
{
    //add nodes if they don't already exist in graph
    if (!mapping->contains(name1))
    {
        node n1;                                                    /// use new????
        n1.name = name1;
        V.push_back(n1);
        mapping->insert(name1, &V.back());
        cout << name1 << ": " << &V.back() << "\n";
    }
    if (!mapping->contains(name2))
    {
        node n2;
        n2.name = name2;
        V.push_back(n2);
        mapping->insert(name2, &V.back());
        cout << name2 << ": " << &V.back() << "\n";
    }
    //add edge with destination name2 and cost c
    node *p1 = static_cast<node *> (mapping->getPointer(name1));
    node *p2 = static_cast<node *> (mapping->getPointer(name2));
    edge e;
    e.dest = p2;
    e.cost = c;
    p1->adj.push_back(e);
}

void graph::dijkstra()
{
    string s = getVertex(); //starting node
    heap H = heap(V.size()); //heap to store unknown nodes
    node *ps = static_cast<node *> (mapping->getPointer(s)); //pointer to starting node
    ps->d = 0;
    //all nodes begin as unknown
    list<node>::iterator it;
    for (it = V.begin(); it != V.end(); it++)
    {
        H.insert((*it).name, it->d, &(*it));
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

string graph::getVertex()
{
    string s;
    cout << "Enter name of starting vertex: ";
    cin >> s;
    while (!mapping->contains(s))
    {
        cerr << "Vertex is not in graph! Try again: ";
        cin >> s;
    }
    return s;
}

void graph::output()
{
    list<string> path;
    node* currNode;
    //open output file
    string filename;
    cout << "Enter name of output file: ";
    cin >> filename;
    ofstream fout(filename);
    if (fout.fail())
    {
        cerr << "Error opening output file " << filename << "\n";
        exit(1);
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
                if (name == path.back())
                    break;
                fout << ", ";
            }
        }
        fout << "]\n";
        path.clear();
    }
    fout.close();
}