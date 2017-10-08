//main.cpp
//Camille Chow
//DSA Assignment 1
//April 2017

//This program takes in a text file of commands that will either create, push, or pop
//to and from stacks and queues that contain ints, doubles, and strings
//and writes to an output file as it processes the commands

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "SimpleList.cpp"
#include "Stack.cpp"
#include "Queue.cpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
using namespace std;

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

list<SimpleList<int> *> listSLi; //all integer stacks and queues
list<SimpleList<double> *> listSLd; //all double stacks and queues
list<SimpleList<string> *> listSLs; //all string stacks and queues

ifstream fin; //input file stream
ofstream fout; //output file stream

//-----------------------------------------------------------------------------
// Supporting functions: findList() and processCommand()
//-----------------------------------------------------------------------------

//findList() - searches through the global lists to find a stack/queue of a specified name
//returns NULL if the stack/queue is not found
template <typename T>
SimpleList<T>* findList(list<SimpleList<T>*> l, string n)
{
    typename std::list<SimpleList<T> *>::iterator it = l.begin();
    while (it != l.end())
    {
        if ((*it)->getName() == n)
        {
            return *it;
        }
        ++it;
    }
    return NULL;
}

//processCommand() - given a global list, command type, list name, and value, this function
//finds the specified list and executes the given command on it
template <typename T>
void processCommand(list<SimpleList<T>*> bigList, string name, string command, T value)
{
    string listType; //"stack" or "queue"
    
    SimpleList<T> *lPtr;
    lPtr = findList<T>(bigList, name); //list found after using findList()
    
    //"create" command
    if (command == "create")
    {
        fin >> listType;
        fout << "PROCESSING COMMAND: " << command << " " << name << " " << listType << endl;
        
        //checks if list already exists
        if (lPtr != NULL)
        {
            fout << "ERROR: This name already exists!" << endl;
        }
        else
        {
            //create stack
            if (listType == "stack")
            {
                if (name[0] == 'i')
                {
                    SimpleList<int> *pSLi;
                    pSLi = new Stack<int>(name);
                    listSLi.push_front(pSLi);
                }
                else if (name[0] == 'd')
                {
                    SimpleList<double> *pSLd;
                    pSLd = new Stack<double>(name);
                    listSLd.push_front(pSLd);
                }
                else
                {
                    SimpleList<string> *pSLs;
                    pSLs = new Stack<string>(name);
                    listSLs.push_front(pSLs);
                }
            }
            //create queue
            else
            {
                if (name[0] == 'i')
                {
                    SimpleList<int> *pSLi;
                    pSLi = new Queue<int>(name);
                    listSLi.push_front(pSLi);
                }
                else if (name[0] == 'd')
                {
                    SimpleList<double> *pSLd;
                    pSLd = new Queue<double>(name);
                    listSLd.push_front(pSLd);
                }
                else
                {
                    SimpleList<string> *pSLs;
                    pSLs = new Queue<string>(name);
                    listSLs.push_front(pSLs);
                }
            }
        }
    }
    //"push" command
    else if (command == "push")
    {
        fout << "PROCESSING COMMAND: " << command << " " << name << " " << value << endl;
        
        //checks if list exists
        if (lPtr == NULL)
        {
            fout << "ERROR: This name does not exist!" << endl;
        }
        else
        {
            lPtr->push(value);
        }
    }
    //pop command
    else
    {
        fout << "PROCESSING COMMAND: " << command << " " << name << endl;
        
        //checks if list exists
        if (lPtr == NULL)
        {
            fout << "ERROR: This name does not exist!" << endl;
        }
        else
        {
            //checks if list is empty
            if (lPtr->isEmpty())
            {
                fout << "ERROR: This list is empty!" << endl;
            }
            else
                fout << "Value popped: " << lPtr->pop() << endl;
        }
    }
}

//-----------------------------------------------------------------------------
// main function - asks for input/output file names and cycles through input
//                 file, processing each line
//-----------------------------------------------------------------------------

int main()
{
    string inputFileName;
    string outputFileName;
    string command, name, listType, value;
    bool fileNamesValid = false;
    
    //create files
    while (!fileNamesValid)
    {
        //asks user for input file name
        cout << "Enter name of input file: ";
        cin >> inputFileName;
        
        //checks if file name is valid
        fin.open(inputFileName);
        if (fin.fail() )
        {
            cerr << "Could not open " << inputFileName << "\n";
            continue;
        }
        
        //asks user for output file name
        cout << "Enter name of output file: ";
        cin >> outputFileName;
        
        fout.open(outputFileName);
        fileNamesValid = true;
    }
    
    //process files
    string n,c,v; //name, command, and value
    while (!fin.eof())
    {
        fin >> c;
        fin >> n;
        if (c == "push")
        {
            fin >> v;
        }
        if (!fin.eof())
        {
            //determines data type and converts value type and processes commands accordingly
            if (n[0] == 'i')
            {
                int i = strtol(v.c_str(), NULL, 10);
                processCommand<int>(listSLi, n, c, i);
            }
            else if (n[0] == 'd')
            {
                double d = strtod(v.c_str(), NULL);
                processCommand<double>(listSLd, n, c, d);
            }
            else
            {
                processCommand<string>(listSLs, n, c, v);
            }
        }
    }
    
    //close files
    fin.close();
    fout.close();
    return 0;
}