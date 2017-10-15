//  heap.cpp
//  DSA2 Program 2
//  Camille Chow
//  10/17/17.
//  see header file for function definitions

#include "heap.h"
#include <iostream>
using namespace std;

heap::heap(int capacity)
{
    current_size = 0;
    this->capacity = capacity;
    data.resize(capacity + 1);
    mapping = new hashTable(2*capacity);
}

int heap::insert(const std::string &id, int key, void *pv)
{
    if (current_size >= capacity) {
        return 1;
    }
    if (mapping->contains(id)) {
        return 2;
    }
    
    //increase size of heap and insert node at the end
    current_size++;
    data[current_size].id = id;
    data[current_size].key = key;
    data[current_size].pData = pv;
    
    //store string id in hashtable
    //printf("address to set pointer to: %p\n",&data[current_size]);
    mapping->insert(id,&data[current_size]);
    //printf("hashed with pointer to %d\n\n", getPos(static_cast<node *>(mapping->getPointer(id))));
    
    percolateUp(current_size);
    
    return 0;
}

int heap::setKey(const std::string &id, int key)
{
    node *pn = static_cast<node *> (mapping->getPointer(id));
    
    if (pn == NULL) {
        return 1;
    }
    
    int oldKey = pn->key;
    pn->key = key;
    
    if (key > oldKey) {
        percolateDown(getPos(pn));
    }
    else if (key < oldKey) {
        percolateUp(getPos(pn));
    }
    
    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
    if (current_size == 0) {
        return 1;
    }
    //retrieve relevant data
    if (pId != nullptr) {
        *pId = data[1].id;
    }
    if (pKey != nullptr) {
        *pKey = data[1].key;
    }
    if (ppData != nullptr) {
        *(static_cast<void **> (ppData)) = data[1].pData;
    }
    //remove node
    mapping->remove(data[1].id);
    data[1] = data[current_size--];
    percolateDown(1);
    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData)
{
    if (!mapping->contains(id)) {
        return 1;
    }
    
    node *pn = static_cast<node *> (mapping->getPointer(id));
    int pos = getPos(pn);
    
    //retrieve relevant data
    if (pKey != nullptr) {
        *pKey = pn->key;
    }
    if (ppData != nullptr) {
        *(static_cast<void **> (ppData)) = pn->pData;
    }
    //remove node
    mapping->remove(pn->id);
    data[pos] = data[current_size--];
    percolateDown(pos);
    
    return 0;
}

void heap::percolateDown(int posCur)
{
    int child;
    node tmp = data[posCur];
    
    while (posCur*2 <= current_size) {
        
        //find smallest child
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
        posCur = child;
    }
    data[posCur] = tmp;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

void heap::percolateUp(int posCur)
{
    node tmp = data[posCur];
    
    while (posCur > 1 && tmp.key < data[posCur/2].key) {
        data[posCur] = data[posCur/2];
        mapping->setPointer(data[posCur].id, &data[posCur]);
        posCur /= 2;
    }
    data[posCur] = tmp;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

int heap::getPos(node *pn)
{
    int p = pn - &data[0];
    return p;
}