#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"
#include <string>
#include <list>
#include <climits>
using namespace std;

class graph {
    
public:
    // insert: inserts vertex/edge into graph with given name
    void insert(const string &name1, const string &name2, int c);
    // dijkstra: runs algorithm on graph
    void dijkstra(const string &s);
    // prints results to specified output file
    // returns:
    //  0 on success
    //  -1 on fopen error
    int output(const string fname);
    
private:
    
    class edge;
    
    class node {
    public:
        string name; // The name of this node
        node* p = NULL; //pointer to previous node
        int d = INT_MAX; // dv for dijkstra
        bool known = false;
        list<edge> adj; // Adjacency list
    };
    
    class edge {
    public:
        node* dest; // destination node
        int cost; // cost of edge
    };
    
    list<node> V; // List of vertices in graph
    hashTable *mapping; // mapping of vertices
};

#endif //_GRAPH_H