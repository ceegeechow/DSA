#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string deMerge(string A, string B, string C)
{
    return C;
}

int main()
{
    string infile, outfile, A, B, C;
    cout << "Enter name of input file: ";
    cin >> infile;
    ifstream fin(infile);
    if (fin.fail())
    {
        cerr << "Error opening input file " << infile << "\n";
        return -1;
    }
    cout << "Enter name of output file: ";
    cin >> outfile;
    ofstream fout(outfile);
    if (fout.fail())
    {
        cerr << "Error opening output file " << outfile << "\n";
        return -1;
    }
    while (!fin.eof())
    {
        fin >> A >> B >> C;
        fout << deMerge(A,B,C) << "\n";
    }
    return 0;
}