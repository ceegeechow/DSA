#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int M[1000][1000];
int n,m;

bool isMerge(string A, string B, string C, int i, int j, int k)
{
    if (i > n || j > m)
        return false;
    if (k >= C.length())
        return false;
    if (((i == 0 && j == 0) || (i != 0 && A[i-1] == C[k]) || (j != 0 && B[j-1] == C[k])) && M[i][j] != 1) //ugly af!
    {
        M[i][j] = 1;
        k++;
        if (!isMerge(A,B,C,i+1,j,k)) //if statement necessary???
            isMerge(A,B,C,i,j+1,k);
        return true;
    }
    return false;
}

string deMerge(string A, string B, string C)
{
    int k = C.length() - 1;
    int i = n;
    int j = m;
    while (k >= 0)// i > 0 && j > 0) //or???
    {
        if (B[j - 1] == C[k])
            j--;
        else
        {
            C[k] = toupper(C[k]);
            i--;
        }
        k--;
    }
    return C;
}

void clearM()
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
            M[i][j] = 0;
    }
}

int main()
{
//    string infile, outfile, A, B, C;
//    cout << "Enter name of input file: ";
//    cin >> infile;
//    ifstream fin(infile);
//    if (fin.fail())
//    {
//        cerr << "Error opening input file " << infile << "\n";
//        return -1;
//    }
//    cout << "Enter name of output file: ";
//    cin >> outfile;
//    ofstream fout(outfile);
//    if (fout.fail())
//    {
//        cerr << "Error opening output file " << outfile << "\n";
//        return -1;
//    }
//    while (!fin.eof())
//    {
//        fin >> A >> B >> C;
//        n = A.length();
//        m = B.length;
//        clearM();
//        if (isMerge(A,B,C,0,0,0))
//            fout << deMerge(A,B,C) << "\n";
//        else
//            fout << "*** NOT A MERGE ***\n";
//    }
    string A = "chocolate";
    string B = "chip";
    string C = "cchocholaipte";
    printf("result: %d\n", isMerge(A,B,C,0,0,0));
    string D = "cchocholaiptes";
    printf("result: %d\n", isMerge(A,B,D,0,0,0));
    return 0;
}