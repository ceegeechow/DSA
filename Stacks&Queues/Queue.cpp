//Queue.cpp
//Camille Chow
//DSA Assignment 1
//April 2017

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <string>
using namespace std;

//-----------------------------------------------------------------------------
// Queue class definition - derived from SimpleList class
// Public members:  Queue() - same constructor as SimpleList
//                  push() - utilizes insertEnd function from SimpleList class
//                  pop() - utilizes removeStart function from SimpleList class
//-----------------------------------------------------------------------------

template <typename T>
class Queue : public SimpleList<T>
{
public:
    Queue(string n):SimpleList<T>(n) {}
    
    void push(T d)
    {
        SimpleList<T>::insertEnd(d);
    }
    
    T pop()
    {
        return SimpleList<T>::removeStart();
    }
};