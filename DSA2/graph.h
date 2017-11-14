#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"
#include <string>
#include <list>
#include <climits>
using namespace std;

class graph
{
public:
    // insert: inserts vertices/edge into graph with given names/cost
    void insert(const string &name1, const string &name2, int c);
    // dijkstra: runs algorithm on graph
    void dijkstra(const string &s);
    // prints results to specified output file
    // returns:
    //  0 on success
    //  -1 on open error
    int output(const string fname);
    
private:
    class edge; //defined below
    
    // nested node class
    // each node represents a vertex in the graph
    class node
    {
    public:
        string name; // The name of this node
        node* p = NULL; //pointer to previous node (for dijkstra)
        int d = INT_MAX; // path weight (for dijkstra)
        bool known = false; // (for dijkstra)
        list<edge> adj; // Adjacency list
    };
    
    // nested edge class
    // each edge stored in the source node's adjacency list
    class edge
    {
    public:
        node* dest; // destination node
        int cost; // cost of edge
    };
    
    list<node> V; // List of vertices in graph
    hashTable *mapping; // mapping of vertices
};

#endif //_GRAPH_H