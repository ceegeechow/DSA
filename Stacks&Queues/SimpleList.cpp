//SimpleList.cpp
//Camille Chow
//DSA Assignment 1
//April 2017

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <string>
using namespace std;

//-----------------------------------------------------------------------------
// SimpleList class definition:
// Defines a singly linked circular list with one sentinel node
//
// Private members: Node, name, head, end
//
// Protected members:  removeStart()
//                     insertStart()
//                     insertEnd()
//
// Public members:  SimpleList()
//                  isEmpty()
//                  getName()
//                  push() - pure virtual function
//                  pop() - pure virtual function
//-----------------------------------------------------------------------------

template <typename T>
class SimpleList
{
private:
    struct Node
    { //definition of a node - contains data and pointer to the next node
        T data;
        Node *next;

        Node(T d, Node * nxt)
        {
            data = d;
            next = nxt;
        }
        Node() {}
    };

    string name;
    Node *head;
    Node *end;
    
protected:
    T removeStart()
    { //tells head to point to the node after the current first node
        Node * startNode = head->next;
        T data = startNode->data;
        head->next = startNode->next;
//        if (isEmpty()) {
//            end = startNode;
//        }
        return data;
    }
    
    void insertStart(T d)
    { //creates new node at beginning and tells head to point to it
        Node * newNode = new Node(d,head->next);
        if (isEmpty()) {
            end = newNode;
        }
        head->next = newNode;
        return;
    }
    
    void insertEnd(T d)
    { //creates new node at end and tells end to point to it
        Node * newNode = new Node(d,head);
        end->next = newNode;
        end = newNode;
    }

public:
    SimpleList(string n)
    { //SimpleList constructor
        name = n;
        Node * sent = new Node();
        head = sent;
        sent->next = head;
        end = head;
    }
    
    bool isEmpty()
    { //returns true if list is empty
        if (head->next == head)
            return true;
        return false;
    }
    
    string getName()
    { //returns name of list
        return name;
    }
    
    //virutal functions - to be defined in Stack and Queue classes
    virtual void push(T d) = 0;
    virtual T pop() = 0;
};