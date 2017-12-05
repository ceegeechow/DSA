#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int M[1000][1000];
int n,m,k;
string A, B, C;

void printM(int a, int b)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (a == i && b == j) {
                printf("*");
            }
            printf("%d\t",M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool isMerge(int i, int j)
{
    printf("%s k: %d\n",C.c_str(), k);
    printM(i,j);
    //check for out of bounds
    if (i > n || j > m)
    {
        //printf("false\n");
        return false;
    }
    //check for last box
    if (i == n && j == m && k == C.length())           //is this correct/enough???
    {
        return true;
    }
    //check if you've been to current box
    if (!M[i][j])
    {
        return false;
    }
    //check if box below matches the next char
    if (toupper(A[i]) == toupper(C[k]))
    {
        C[k] = toupper(C[k]);
        k++;
        return isMerge(i+1,j);
    }
    //check if box to the right matches
    else
    {
        M[i+1][j] = false;
        if (toupper(B[j]) == toupper(C[k]))
        {
            k++;
            return isMerge(i,j+1);
        }
        else
        {
            M[i][j+1] = false;              //necessary??? (not for chocolate chips)
            return false;
        }
    }
}

void clearM()
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
            M[i][j] = 1;
    }
    k = 0;
}

int main()
{
//    string infile, outfile;
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
//        m = B.length();
//        clearM();
//        if (isMerge(0,0))
//            fout << C << "\n";
//        else
//            fout << "*** NOT A MERGE ***\n";
//    }
    A = "ab";
    B = "ba";
    C = "abab";
    n = A.length();
    m = B.length();
    clearM();
    printf("C: %s, result: %d\n", C.c_str(), isMerge(0,0));
    return 0;
}