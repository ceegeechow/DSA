//  spellcheck.cpp
//  DSA2 Program 1
//  Camille Chow
//  9/26/17.

#include <stdio.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include "hash.h"
using namespace std;

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

ifstream fin; //input file stream
ofstream fout; //output file stream

//-----------------------------------------------------------------------------
// Supporting function - isValid()
// returns true if character is a letter, digit, dash, or apostrophe
//-----------------------------------------------------------------------------

bool isValid(char c) {
    return ((c>=97&&c<=122)||(c>=48&&c<=57)||(c==45)||(c==39));
}

//-----------------------------------------------------------------------------
// Main Loop
//-----------------------------------------------------------------------------

int main() {
    
    string dict_name, in_filename, out_filename;
    bool fileNamesValid = false;
    
    //ask for dictionary name
    while (!fileNamesValid) {
        
        cout << "Enter name of dictionary: ";
        cin >> dict_name;
        
        //checks if file name is valid
        fin.open(dict_name);
        if (fin.fail() ) {
            cerr << "Could not open " << dict_name << "\n";
            continue;
        }
        
        fileNamesValid = true;
    }
    
    //create hashtable
    hashTable* table = new hashTable(100000);
    
    string word;
    
    //start timing dictionary loading
    clock_t t1 = clock();
    
    //load each word into hashtable
    while (!fin.eof()) {
        fin >> word;
        //convert all characters to lower case
        for (int i = 0; i < word.length(); i++) {
            word[i] = tolower(word[i]);
        }
        //if rehashing fails, exit
        if (table->insert(word) == 2) {
            cerr << "Error rehashing hash table, exiting program\n";
            return -1;
        }
    }
    clock_t t2 = clock();
    fin.close();
    
    //print time to load
    double timeDiff1 = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: " << timeDiff1 << "\n";
    
    //ask for input file
    fileNamesValid = false;
    
    while (!fileNamesValid) {
        
        cout << "Enter name of input file: ";
        cin >> in_filename;
        
        //checks if file name is valid
        fin.open(in_filename);
        if (fin.fail()) {
            cerr << "Could not open " << in_filename << "\n";
            continue;
        }
        
        fileNamesValid = true;
    }
    
    //ask for output file
    cout << "Enter name of output file: ";
    cin >> out_filename;
    
    fout.open(out_filename);
    
    //start timing spellcheck
    clock_t t3 = clock();
    
    //check document
    string currentWord = "";
    char c;
    bool longWord = false;
    bool ignore = false;
    int lineNum = 1;
    
    while (!fin.eof()) {
        //get character from text file
        c = tolower(fin.get());
        //if character is valid, add to current word (unless part of a long word)
        if (isValid(c)) {
            if (!longWord) {
                
                if (currentWord.length() < 20) {
                    currentWord = currentWord + c;
                }
                else {
                    fout << "Long word at line " << lineNum << ", starts: " << currentWord << "\n";
                    longWord = true;
                    currentWord = "";
                }
                //ignore word if it contains digits
                if (isdigit(c)) {
                    ignore = true;
                }
            }
            else {
                continue;
            }
        }
        //if character isn't valid, check current word (if there is one)
        else {
            if (currentWord != "" && !ignore) {
                if (!table->contains(currentWord)) {
                    fout << "Unknown word at line " << lineNum << ": " << currentWord << "\n";
                }
            }
            currentWord = "";
            longWord = false;
            ignore = false;
        }
        //if newline character, increment line #
        if (c == '\n'){
            lineNum ++;
        }
    }
    clock_t t4 = clock();
    fin.close();
    
    //print time to spellcheck
    double timeDiff2 = ((double) (t4 - t3)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to check document: " << timeDiff2 << "\n";
    
    return 0;
}