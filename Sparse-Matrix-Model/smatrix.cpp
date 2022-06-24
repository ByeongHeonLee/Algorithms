#include <iomanip>
#include <algorithm>
#include "smatrix.h"

using std::istream;
using std::ostream;

smatrix::smatrix(int r, int c, int t)
    : rows(r), cols(c), terms(t), capacity(1)
{
    smArray = new mterm[capacity];
}

smatrix::smatrix(smatrix &oprd)
    : rows(oprd.rows), cols(oprd.cols), terms(oprd.terms), capacity(oprd.capacity)
{
    smArray = new mterm[capacity];
    for (int i = 0; i < terms; i++)
    {
        smArray[i].row = oprd.smArray[i].row;
        smArray[i].col = oprd.smArray[i].col;
        smArray[i].value = oprd.smArray[i].value;
    }
}

smatrix::smatrix(const int **oprd, int r, int c) : rows(r), cols(c), terms(0), capacity(r * c)
{
    mterm *temp = new mterm[capacity];

    int t = 0;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (oprd[i][j]) //oprd[i][j] != 0
            {
                temp[t].row = i;
                temp[t].col = j;
                temp[t++].value = oprd[i][j];
            }

    terms = t;
    capacity = t + 1;

    smArray = new mterm[capacity];
    for (int i = 0; i < terms; i++)
    {
        smArray[i].row = temp[i].row;
        smArray[i].col = temp[i].col;
        smArray[i].value = temp[i].value;
    }
    delete[] temp;
}

smatrix::~smatrix()
{
    delete[] smArray;
}

smatrix operator-(const smatrix &oprd)
{
    smatrix result(oprd);
    for (int i = 0; i < oprd.terms; i++)
        result.smArray[i].value *= -1;
    return result;
}

// 연산 결과가 0인 경우에 대한 처리
// 덧셈 연산 성능 개선

smatrix smatrix::operator+(const smatrix &oprd)
{
    if (rows != oprd.rows || cols != oprd.cols)
        throw "Incompatible matrices";

    smatrix result(*this);
    for (int i = 0; i < terms; i++)
        for (int j = 0; j < oprd.terms; j++)
            if (smArray[i].row == oprd.smArray[i].row && smArray[i].col == oprd.smArray[i].col)
                smArray[i].value += oprd.smArray[i].value;
    return result;
}

smatrix smatrix::operator-(const smatrix &oprd)
{
    return *this + -oprd;
}

smatrix smatrix::operator*(const smatrix &oprd)
{ // matrix A(this) * matrix oprd
    if (cols != oprd.rows)
        throw "Incompatible matrices";

    smatrix oprdXpose = oprd.transpose();
    smatrix result(rows, oprd.cols, 0);

    int currRowIndex = 0;
    int currRowBegin = 0;
    int currRowA = smArray[0].row;

    if (terms == capacity)
        changeSize(terms + 1);
    oprdXpose.changeSize(oprdXpose.terms + 1);
    smArray[terms].row = rows;
    oprdXpose.smArray[oprd.terms].row = oprd.cols;
    oprdXpose.smArray[oprd.terms].col = -1;

    int sum = 0;
    while (currRowIndex < terms)
    {
        int currColOprd = oprdXpose.smArray[0].row;
        int currColIndex = 0;
        while (currColIndex <= oprd.terms)
        {
            if (smArray[currRowIndex].row != currRowA)
            {
                result.storeSum(sum, currRowA, currColOprd);
                sum = 0;
                currRowIndex = currRowBegin;
                while (oprdXpose.smArray[currColIndex].row == currColOprd)
                    currColIndex++;
                currColOprd = oprdXpose.smArray[currColIndex].row;
            }
            else if (oprdXpose.smArray[currColIndex].row != currColOprd)
            {
                result.storeSum(sum, currRowA, currColOprd);
                sum = 0;
                currRowIndex = currRowBegin;
                currColOprd = oprdXpose.smArray[currColIndex].row;
            }
            else if (smArray[currRowIndex].col < oprdXpose.smArray[currColIndex].col)
                currRowIndex++;
            else if (smArray[currRowIndex].col == oprdXpose.smArray[currColIndex].col)
            {
                sum += smArray[currRowIndex].value * oprdXpose.smArray[currColIndex].value;
                currRowIndex++;
                currColIndex++;
            }
            else
                currColIndex++;
        }
        while (smArray[currRowIndex].row == currRowA)
            currRowIndex++;
        currRowBegin = currRowIndex;
        currRowA = smArray[currRowIndex].row;
    }
    return result;
}

smatrix smatrix::transpose()
{
    smatrix result(cols, rows, terms);

    if (terms > 0)
    {
        int *rowSize = new int[cols];
        int *rowStart = new int[cols];

        std::fill(rowSize, rowSize + cols, 0);
        for (int i = 0; i < terms; i++)
            rowSize[smArray[i].col]++;

        rowStart[0] = 0;
        for (int i = 1; i < cols; i++)
            rowStart[i] = rowStart[i - 1] + rowSize[i - 1];

        for (int i = 0; i < terms; i++)
        {
            int j = rowStart[smArray[i].col];
            result.smArray[j].row = smArray[i].col;
            result.smArray[j].col = smArray[i].row;
            result.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;
        }

        delete[] rowSize;
        delete[] rowStart;
    }
    return result;
}

ostream &operator<<(ostream &os, const smatrix &smat)
{
    int zero = 0;
    int t = 0;

    for (int i = 0; i < smat.rows; i++)
    {
        os << "|";
        for (int j = 0; j < smat.cols; j++)
        {
            if (smat.smArray[t].row == i && smat.smArray[t].col == j)
                os << std::setw(5) << " " << smat.smArray[t].value << " ";
            else
                os << std::setw(5) << " " << zero << " ";
        }
        os << "|\n";
    }
}

void smatrix::storeSum(const int sum, const int r, const int c)
{
    if (sum != 0)
    {
        if (terms == capacity)
            changeSize(2 * capacity);
        smArray[terms].row = r;
        smArray[terms].col = c;
        smArray[terms++].value = sum;
    }
}

void smatrix::changeSize(const int newSize)
{
    if (newSize < terms)
        throw "New size must be greater than number of terms";

    mterm *temp = new mterm[newSize];
    std::copy(smArray, smArray + terms, temp);
    delete[] smArray;
    smArray = temp;
    capacity = newSize;
}
