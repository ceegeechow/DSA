//  heap.cpp
//  DSA2 Program 2
//  Camille Chow
//  10/17/17.
//  see header file for function definitions

#include "heap.h"

heap::heap(int capacity) {
    
    current_size = 0;
    this.capacity = capacity;
    data.resize(capacity + 1);
    
    //create hashtable
    mapping = new hashTable(2*capacity);
}

int heap::insert(const std::string &id, int key, void *pv = NULL) {
    
    if (current_size == capacity) {
        return 1;
    }
    if (!hash_p->contains(id)) {
        return 2;
    }
    
    current_size++;
    data[current_size].id = id;
    data[current_size].key = key;
    data[current_size].pv = pv;
    
    percolateUp(current_size);
    
    //store string id in hashtable
    mapping->insert(id,&data[current_size]);
    
    return 0;
}

int heap::setKey(const std::string &id, int key) {
    
    bool b;
    node *pn = static_cast<node *> (mapping->getPointer(id, &b));
    
    if (!b) {
        return 1;
    }
    
    oldKey = pn->key;
    pn->key = key;
    
    if (key > oldKey) {
        percolateDown(getPos(pn));
    }
    else if (key < oldKey) {
        percolateUp(getPos(pn));
    }
    
    return 0;
}
// deleteMin - return the data associated with the smallest key
//             and delete that node from the binary heap
//
// If pId is supplied (i.e., it is not NULL), write to that address
// the id of the node being deleted. If pKey is supplied, write to
// that address the key of the node being deleted. If ppData is
// supplied, write to that address the associated void pointer.
//
// Returns:
//   0 on success
//   1 if the heap is empty
int heap::deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL)
{
    if () {
        
    }
}
// remove - delete the node with the specified id from the binary heap
//
// If pKey is supplied, write to that address the key of the node
// being deleted. If ppData is supplied, write to that address the
// associated void pointer.
//
// Returns:
//   0 on success
//   1 if a node with the given id does not exist
int heap::remove(const std::string &id, int *pKey = NULL, void *ppData = NULL)
{
    
}

void heap::percolateDown(int posCur)
{
    int child;
    node tmp = data[posCur];
    
    while (posCur*2 <= current_size) {
        
        child = posCur*2;
        if (child != current_size && data[child+1].key < data[child].key) {
            child++;
        }
        if (data[child].key < tmp.key) {
            data[posCur] = data[child];
            mapping->setPointer(data[posCur].id, &data[posCur]);
        }
        else {
            break;
        }
        data[posCur] = tmp;
        posCur = child;
    }
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

void heap::percolateUp(int posCur)
{
    while (posCur > 1 && data[posCur].key < data[posCur/2].key) {
        data[posCur] = data[posCur/2];
        mapping->setPointer(data[posCur].id, &data[posCur]);
        posCur /= 2;
    }
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

int heap::getPos(node *pn)
{
    int pos = pn - &data[0];
    return pos;
}

//check for off by one errors (capacity and current_size)