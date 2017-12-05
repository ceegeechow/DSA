#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int M[1000][1000];              //boolean!
int n,m;
string A, B, C;

//void printM(int a, int b)
//{
//    for (int i = 0; i <= n; i++)
//    {
//        for (int j = 0; j <= m; j++)
//        {
//            if (a == i && b == j) {
//                printf("*");
//            }
//            printf("%d\t",M[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n");
//}

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
    //check if you've been to current box           why???
    if (M[i][j] == 0)
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
    M[i][j] = 0;
    return false;
}

void clearM()
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
            M[i][j] = 1;
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
        else
            fout << "*** NOT A MERGE ***\n";
    }
//    A = "ab";
//    B = "ba";
//    C = "abab";
//    A = "chocolate";
//    B = "chips";
//    C = "cchocholaiptes";
//    n = A.length();
//    m = B.length();
//    clearM();
//    printf("C: %s, result: %d\n", C.c_str(), isMerge(0,0));
    return 0;
}