#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"
#include <string>
#include <list>
#include <climits>
#include <fstream>

class graph
{
public:
    // constructor: initializes hashTable
    graph();
    // makeGraph: takes input file and creates graph from it
    void makeGraph();
    // insert: inserts vertices/edge into graph with given names/cost
    void insert(const std::string &name1, const std::string &name2, int c);
    // dijkstra: runs algorithm on graph
    void dijkstra();
    // getVertex: gets name of starting vertex for dijkstras alogrithm
    std::string getVertex();
    // output: prints results to specified output file
    void output();
    
private:
    class edge; //defined below
    
    // nested node class
    // each node represents a vertex in the graph
    class node
    {
    public:
        std::string name; // The name of this node
        node* p = NULL; //pointer to previous node (for dijkstra)
        int d = INT_MAX; // path weight (for dijkstra)
        bool known = false; // (for dijkstra)
        std::list<edge> adj; // Adjacency list
    };
    
    // nested edge class
    // each edge stored in the source node's adjacency list
    class edge
    {
    public:
        node* dest; // destination node
        int cost; // cost of edge
    };
    
    std::list<node> V; // List of vertices in graph
    hashTable *mapping; // mapping of vertices
};

#endif //_GRAPH_H