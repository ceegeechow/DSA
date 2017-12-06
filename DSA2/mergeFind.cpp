#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool M[1001][1001];
int n,m;
string A, B, C;

bool isMerge(int i, int j)
{
    //check for out of bounds
    if (i > n || j > m)
    {
        return false;
    }
    //check for last box
    if (i == n && j == m)
    {
        return true;
    }
    //check if you've been to current box
    if (!M[i][j])
    {
        return false;
    }
    //check if box below matches the next char
    if (A[i] == C[i+j] && isMerge(i+1,j))
    {
        C[i+j] = toupper(C[i+j]);
        return true;
    }
    //check if box to the right matches
    if (B[j] == C[i+j] && isMerge(i,j+1))
    {
        return true;
    }
    M[i][j] = false;
    return false;
}

void clearM()
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
            M[i][j] = true;
    }
}

int main()
{
    string infile, outfile;
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
        n = A.length();
        m = B.length();
        clearM();
        if (n+m == C.length() && isMerge(0,0))
            fout << C << "\n";
        else if (!fin.eof())
            fout << "*** NOT A MERGE ***\n";
    }
    return 0;
}