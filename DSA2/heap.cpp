//  heap.cpp
//  DSA2 Program 2
//  Camille Chow
//  10/17/17.
//  see header file for function definitions

#include "heap.h"

heap::heap(int capacity);

int heap::insert(const std::string &id, int key, void *pv = NULL);

int heap::setKey(const std::string &id, int key);

int heap::deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL);

int heap::remove(const std::string &id, int *pKey = NULL, void *ppData = NULL);