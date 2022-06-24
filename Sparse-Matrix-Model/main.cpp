#include <iostream>
#include "smatrix.h"

using namespace std;

int main()
{
    int matArray[4][5] = {{4, 0, 5, 0, 1}, {11, 131, 0, 3, 0}, {0, 0, 0, 0, 17}, {0, -34, -12, 0, 0}};
    smatrix mat(matArray, 4, 5);
    // mat.storeSum(4,0,0);
    // mat.storeSum(5,0,2);
    // mat.storeSum(1,0,4);

    // mat.storeSum(11,1,0);
    // mat.storeSum(131,1,1);
    // mat.storeSum(3,1,3);
    // mat.storeSum(17,2,4);
    // mat.storeSum(-34,3,1);
    // mat.storeSum(-12,3,2);

    cout << mat;
}