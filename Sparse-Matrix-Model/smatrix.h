#ifndef _SMATRIX_H_
#define _SMATRIX_H_

#include <iostream>
#include <iomanip>
#include <algorithm>

using std::istream;
using std::ostream;

class smatrix;

class mterm
{
    friend class smatrix;

private:
    int row;
    int col;
    int value;
};

class smatrix
{
private:
    int rows;       // # of row
    int cols;       // # of column
    int terms;      // # of term
    int capacity;   // Currnet size of array "smArray"
    mterm *smArray; // Array of terms of matrix

public: // Constructors
    smatrix(int r, int c, int t);
    smatrix(smatrix &oprd);
    smatrix(const int **oprd, int r, int c);
    ~smatrix();

public: // Operators
    friend smatrix operator-(const smatrix &oprd); // Negation
    smatrix operator+(const smatrix &oprd);
    smatrix operator-(const smatrix &oprd);
    smatrix operator*(const smatrix &oprd);
    smatrix transpose();

public: // IO
    friend ostream &operator<<(ostream &os, const smatrix &smat);

public:
    void storeSum(const int sum, const int r, const int c);
    void changeSize(const int newSize); // Change size of array "smArray" to newSize
};


#endif