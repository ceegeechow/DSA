//  hash.cpp
//  DSA2 Program 1
//  Camille Chow
//  9/26/17.
//  see header file for function definitions

#include "hash.h"

unsigned int primes[] = {98317, 196613, 393241, 786433, 1572869, 3145739};
const int PRIMES_SIZE = sizeof(primes)/sizeof(int);

hashTable::hashTable(int size)
{
    filled = 0;
    capacity = getPrime(size);
    data.resize(capacity);
    
    for (int i = 0; i < capacity; i++) {
        data[i].isOccupied = false;
        data[i].isDeleted = false;
    }
}

int hashTable::insert(const std::string &key, void *pv)
{
    int p = hash(key);
    //linear probing
    while (data[p].isOccupied) {

        if (data[p].key == key) {
            if (data[p].isDeleted) {
                data[p].isDeleted = false;
                data[p].pv = pv;
                return 0;
            }
            return 1;
        }
        p++;
        if (p >= capacity) {
            p = 0;
        }
    }
    
    data[p].key = key;
    data[p].isOccupied = true;
    data[p].isDeleted = false;
    data[p].pv = pv;
    filled++;
    
    //rehash if table is more than half filled, return 2 if fails
    if (((double)filled/(double)capacity > .5) && !rehash()) {
        return 2;
    }
    
    return 0;
}

bool hashTable::contains(const std::string &key)
{
    if (findPos(key) == -1) {
        return false;
    }
    else {
        return true;
    }
}

void* hashTable::getPointer(const std::string &key, bool *b)
{
    int pos = findPos(key);
    if (pos < 0) {
        if (b != NULL) {
            *b = false;
        }
        return NULL;
    }
    if (b != NULL) {
        *b = true;
    }
    return data[pos].pv;
}

int hashTable::setPointer(const std::string &key, void *pv)
{
    int pos = findPos(key);
    if (pos < 0) {
        return 1;
    }
    data[pos].pv = pv;
    return 0;
}

bool hashTable::remove(const std::string &key)
{
    int pos = findPos(key);
    if (pos < 0) {
        return false;
    }
    data[pos].isDeleted = true;
    return true;
}

int hashTable::hash(const std::string &key)
{
    int hashVal = 0;
    for (int i = 0; i < key.length(); i++) {
        hashVal = 37*hashVal + key[i];
    }
    hashVal %= capacity;
    
    if (hashVal < 0) {
        hashVal += capacity;
    }
    return hashVal;
}

int hashTable::findPos(const std::string &key)
{
    int i = hash(key);
    //linear probing
    while (data[i].isOccupied) {
        if (data[i].key == key) {
            if (data[i].isDeleted) {
                return -1;
            }
            return i;
        }
        i++;
        if (i >= capacity) {
            i = 0;
        }
    }
    return -1;
}

bool hashTable::rehash()
{
    std::vector<hashItem> oldData = data;
    
    capacity = getPrime(2 * oldData.size());
    
    //if memory allocation fails, return false
    try {
        data.resize(capacity);
    } catch (std::bad_alloc) {
        return false;
    }
    //clear table
    for (int i = 0; i < data.size(); i++) {
        data[i].isOccupied = false;
        data[i].isDeleted = false;
    }
    filled = 0;
    //insert old data
    for (int j = 0; j < oldData.size(); j++) {
        if (oldData[j].isOccupied && !oldData[j].isDeleted) {
            insert(oldData[j].key,oldData[j].pv);
        }
    }
    return true;
}

unsigned int hashTable::getPrime(int size)
{
    for (int i = 0; i < PRIMES_SIZE; i++) {
        if (primes[i] >= size) {
            return primes[i];
        }
    }
    return primes[PRIMES_SIZE - 1];
}