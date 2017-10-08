//Stack.cpp
//Camille Chow
//DSA Assignment 1
//April 2017

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <string>
using namespace std;

//-----------------------------------------------------------------------------
// Stack class definition - derived from SimpleList class
// Public members:  Stack() - same constructor as SimpleList
//                  push() - utilizes insertStart function from SimpleList class
//                  pop() - utilizes removeStart function from SimpleList class
//-----------------------------------------------------------------------------

template <typename T>
class Stack : public SimpleList<T>
{
public:
    Stack(string n):SimpleList<T>(n) {}

    void push(T d)
    {
        SimpleList<T>::insertStart(d);
    }
    
    T pop()
    {
        return SimpleList<T>::removeStart();
    }
};