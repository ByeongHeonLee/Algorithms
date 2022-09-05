// Header Files
#include <iostream>
#include <string>

// Namespace & Aliases
using std::string;
using std::to_string;
typedef string String;
typedef long long Digit; // Digit Scale
const char CHAR_OFFSET = '0';

// Functions
String get_binomial_coefficient(int n, int k);
String add_str(String a, String b, size_t base = 10);

/*
 *  Function Name : get_binomial_coefficient
 *  Parameters    : 1) n (int) : # of total elements (Set)
 *                  2) k (int) : # of distinct elements (Subset)
 *  Return Type   : INT (Any integer type, depends on programmer)
 *  Description   : Return the result value of n choose k (nCk)
 */
String get_binomial_coefficient(int n, int k)
{

    // Heap Allcation
    String **combTable = new String *[n + 1];
    for (int i = 0; i < n + 1; i++)
    {
        combTable[i] = new String[n + 1];
        combTable[i][0] = '1'; // nC0 = 1
        combTable[i][i] = '1'; // nCn = 1
    }

    k = (n - k > k) ? k : n - k; // nCk = nCn-k (short cut)

    // Calculation based on formula: nCk = n-1Ck-1 + n-1Ck
    for (int i = 2; i < n + 1; i++)
        for (int j = 1; j < i && j <= k; j++)
            combTable[i][j] = add_str(combTable[i - 1][j - 1], combTable[i - 1][j]);

    // Set result (nCk)
    String result = combTable[n][k];

    // Heap Deallocation
    for (int i = n; i > -1; i--)
        delete[] combTable[i];
    delete[] combTable;

    // Return result (nCk)
    return result;
}

String add_str(String a, String b, size_t base)
{
    size_t size_a = a.size();
    size_t size_b = b.size();

    if (size_a == 0)
        return b;
    if (size_b == 0)
        return a;

    String big_num = size_a > size_b ? a : b;
    String small_num = size_a > size_b ? b : a;
    
    String result = "";

    Digit idx_big = big_num.size() - 1;
    Digit idx_small = small_num.size() - 1;
    bool carry = 0;
 
    while (idx_small > -1)
    {
        // int sum = atoi(&big_num[idx_big]) + atoi(&small_num[idx_small]) + carry;
        int sum = (big_num[idx_big] - CHAR_OFFSET) + (small_num[idx_small] - CHAR_OFFSET) + carry;
        carry = sum / base;
        sum %= base;

        result = to_string(sum) + result;

        idx_big--;
        idx_small--;
    }

    while (idx_big > -1)
    {
        int sum = (big_num[idx_big] - CHAR_OFFSET) + carry;
        carry = sum / base;
        sum %= base;

        result = to_string(sum) + result;

        idx_big--;
    }

    if(carry)
        result = "1" + result;

    return result;
}
