#include <iostream>
#include <string>
#include "polynomial.h"

using namespace std;

int main(){
    polynomial test("+ 1000x^+4 -10x^+3 -   3x ^ +  2  + 7 1 3 x ^ +1   - 1 0 x^ +0    ");
    polynomial test1;
    polynomial test2("-6x^+2 + 4x^+1");
    string testPoly = "+3x^+2 + 5x^+1 - 7x^+0";
    test1 = testPoly;
    cout << test1 << endl;
    cout << test1 + test2 << endl;
    cout << test1 - test2 << endl;
    cout << -test2 << endl;
    cout << test1 * test2 << endl;
    return 0;
}
