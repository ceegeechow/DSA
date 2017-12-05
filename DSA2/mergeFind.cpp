#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int M[1000][1000];              //boolean!
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
    k = i+j;
    printf("i: %d, j: %d, k: %d, C: %s\n", i, j, k, C.c_str());
    printM(i,j);
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
    if (M[i][j] == 0)
    {
        return false;
    }
    //check if box below matches the next char
    if (A[i] == C[k] && printf("going down\n") && isMerge(i+1,j))
    {
        C[k] = toupper(C[k]);
        return true;
    }
    printf("down didn't work, going right\n");
    //check if box to the right matches
    if (B[j] == C[k] && printf("going right\n") && isMerge(i,j+1))
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
//        if (n+m == C.length() && isMerge(0,0))
//            fout << C << "\n";
//        else
//            fout << "*** NOT A MERGE ***\n";
//    }
    A = "ab";
    B = "ba";
    C = "abba";
//    A = "chocolate";
//    B = "chips";
//    C = "cchocholaiptes";
    n = A.length();
    m = B.length();
    clearM();
    printf("C: %s, result: %d\n", C.c_str(), isMerge(0,0));
    return 0;
}