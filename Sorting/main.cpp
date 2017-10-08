// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2017

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds one string
class Data {
public:
    string data;
    Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
    string filename;
    cout << "Enter name of input file: ";
    cin >> filename;
    
    ifstream input(filename.c_str());
    if (!input) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }
    
    // The first line indicates the size
    string line;
    getline(input, line);
    stringstream ss(line);
    int size;
    ss >> size;
    
    // Load the data
    for (int i = 0; i < size; i++) {
        string line;
        getline(input, line);
        l.push_back(new Data(line));
    }
    
    input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
    string filename;
    cout << "Enter name of output file: ";
    cin >> filename;
    
    ofstream output(filename.c_str());
    if (!output) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }
    
    // Write the size first
    int size = l.size();
    output << size << endl;
    
    // Write the data
    for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
        output << (*ipD)->data << endl;
    }
    
    output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
    list<Data *> theList;
    loadDataList(theList);
    
    cout << "Data loaded.  Executing sort..." << endl;
    
    clock_t t1 = clock();
    sortDataList(theList);
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    
    cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;
    
    writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.
Data * buckets[1100000] = {};
unsigned int counts[1100000] = {};

void countingSort(list<Data *> &l) {
    for (list<Data *>::const_iterator itr = l.begin(); itr != l.end(); itr++) {
        double temp1 = round((1000*atof(((*itr)->data).c_str())));
        int temp = (int)temp1;
        buckets[temp] = *itr;
        counts[temp]++;
    }
    list<Data *>::iterator itr = l.begin();
    int i = 0;
    while(itr != l.end()){
        while(counts[i]){
            *itr = buckets[i];
            itr++;
            counts[i]--;
        }
        i++;
    }
}

bool comp(Data* d1, Data* d2) { //returns true if d1 < d2
    int j = 20;
    int k = 20;
    while((d1->data)[j] != '.') { j-- ; }
    while((d2->data)[k] != '.') { k-- ; }
    
    if (j == k) {
        return ((d1->data).compare((d2->data)) < 0);
    }
    else {
        return (j < k);
    }
}

void insertionSort(list<Data *> &l) {
    const list<Data *>::iterator begin = l.begin();
    const list<Data *>::iterator end = l.end();
    list<Data *>::iterator itr;
    
    for (list<Data *>::iterator i = next(begin,1); i != end; i++) {
        Data* temp = *i;
        for (itr = i; (itr != begin)&&(comp(temp,*(prev(itr,1)))); itr--) {
            *itr = *(prev(itr,1));
        }
        *itr = temp;
    }
}

Data * storage[200000][10] = {};

void radixSort(list<Data *> &l, list<Data *>::iterator begin, list<Data *>::iterator end, int radix, int max) {
    if ((radix < max) && (begin != end)) {
        unsigned int counts[10] = {};
        for (list<Data *>::iterator itr = begin; itr != end; itr++) {
            int digits = 20;
            int bin;
            while (((*itr)->data)[digits] != '.') {
                digits--;
            }
            if (radix < (20 - digits)) {
                bin = 0;
            }
            else {
                bin = ((*itr) -> data)[radix - (20 - digits)] - 48;
            }
            storage[counts[bin]][bin] = *itr;
            (counts[bin])++;
        }
        list<Data *>::iterator itr = begin;
        list<Data *>::iterator bucket[10];
        
        for (int i = 0; i < 10; i++) {
            bucket[i] = itr;
            for (int j = 0; j < counts[i]; j++) {
                *itr = storage[j][i];
                itr++;
            }
            bucket[i+1] = itr;
        }
        int newRadix = radix + 1;
        for (int k = 0; k < 10; k++) {
            radixSort(l,bucket[k],bucket[k+1],newRadix,max);
        }
    }
}

void sortDataList(list<Data *> &l) {
     //Fill in this function
    if(l.size() < 200000) { //T1 case
        radixSort(l, l.begin(), l.end(), 0, 5);
        insertionSort(l);
    }
    else if(((*l.begin())->data).size() < 8) { //T3 case
        countingSort(l);
    }
    else if(((*l.begin())->data).substr(0,9) == ((*(++l.begin()))->data).substr(0,9)) { //T4 case
        insertionSort(l);
    }
    else { //T2 case
        radixSort(l, l.begin(), l.end(), 0, 6);
        insertionSort(l);
    }
}
