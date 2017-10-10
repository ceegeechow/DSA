//
// This program allows the user to manipulate a binary heap.
// The program only inserts string ids with associated keys
// into the heap. The heap class, however, is capable of storing
// arbitrary pointers along with each heap item.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "heap.h"

using namespace std;

ifstream fin; //input file stream
ofstream fout; //output file stream

// Read an integer from standard input; if a non-integer is in the
// buffer, the state is fixed and the user is re-prompted;
// either way, the remainder of the buffer is cleared
void getInteger(string message, int &ref)
{
    bool inputGood = false;
    while (!inputGood) {
        inputGood = true;
        
        fout << message;
        fin >> ref;
        
        if (!fin) {
            // Non-integer in input buffer, get out of "fail" state
            fin.clear();
            inputGood = false;
        }
        while (fin.get() != '\n'); // clear buffer
    }
}

int main(int argc, char**argv)
{
    int capacity = 0;
    int option;
    string stringTmp;
    int key, id;
    int retVal;
    char* input = argv[1];
    char* output = argv[2];
    fin.open(input);
    fout.open(output);
    
    // Have user choose capacity for binary heap
    getInteger("Choose a capacity for the binary heap: ", capacity);
    
    // Create the heap
    heap myHeap1(capacity);
    
    while (1) {
        fout << "\nOptions:" << endl;
        fout << "1 - Insert a new item into the binary heap" << endl;
        fout << "2 - Set the key of a specified item" << endl;
        fout << "3 - Delete a specified item" << endl;
        fout << "4 - Perform a deleteMin" << endl;
        fout << "5 - Quit" << endl;
        
        // Have the user choose an option
        getInteger("Choose an option: ", option);
        switch(option) {
                
            case 1:
                // Get data to insert into heap from the user and insert it
                
                fout << "Enter an id string (to insert): ";
                getline(fin, stringTmp);
                
                getInteger("Enter an associated integer key: ", key);
                
                retVal = myHeap1.insert(stringTmp, key);
                
                fout << "\nCall to 'insert' returned: " << retVal << endl;
                
                break;
                
            case 2:
                // Get id string and new key from user and change the key
                
                fout << "Enter an id string (to change its key): ";
                getline(fin, stringTmp);
                
                getInteger("Enter an associated integer key: ", key);
                
                retVal = myHeap1.setKey(stringTmp, key);
                fout << "\nCall to 'setKey' returned: " << retVal << endl;
                
                break;
                
            case 3:
                // Get id string from user and delete it from the heap
                
                fout << "Enter an id string (to delete): ";
                getline(fin, stringTmp);
                
                retVal = myHeap1.remove(stringTmp, &key);
                fout << "\nCall to 'delete' returned: " << retVal << endl;
                
                if (retVal == 0) {
                    fout << "\nDeleted item with string id \"" << stringTmp
                    << "\" and key " << key << endl;
                }
                
                break;
                
            case 4:
                // Perform the deleteMin operation on the heap
                
                retVal = myHeap1.deleteMin(&stringTmp, &key);
                fout << "\nCall to 'deleteMin' returned: " << retVal << endl;
                
                if (retVal == 0) {
                    fout << "\nDeleted item with string id \"" << stringTmp
                    << "\" and key " << key << endl;
                }
                
                break;
                
            case 5:
                fout << "\nGoodbye!" << endl;
                fin.close();
                fout.close();
                exit(0);
                
            default:
                cerr << "Error, that input is not valid!" << endl;
                fin.close();
                fout.close();
                exit (1);
        }
    }
    
    cerr << "Error, we should never get here!" << endl;
    exit (1);
}