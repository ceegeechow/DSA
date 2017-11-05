#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"
#include <string>
#include <list>
using namespace std;

class graph {
    
public:
    
    // graph constructor: initializes graph with size 0
    // and initializes hashTable of smallest size
    graph();
    
    // insert: inserts vertex into graph with given name
    // returns:
    //  0 on success
    //  1 if node already exists in graph
    int insert(const std::string &name);
    void getData();
    
private:
    
    class node {
    public:
        string name; // The name of this node
        node* p; //pointer to previous node
        int d; // dv for dijkstra
        bool known;
        list<edge> *adj; // Adjacency list
    };
    
    class edge {
    public:
        node* dest; // destination node
        int c; // cost of edge
    }
    
    list<node> V; // List of vertices in graph
    hashTable *mapping; // mapping of vertices
    int size; //number of vertices in graph
};

#endif //_GRAPH_H