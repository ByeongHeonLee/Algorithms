// Header Files
#include <iostream>
#include <string>
#include <cstdlib>

// Namespace & Aliases
using std::string;
typedef string String;
const char CHAR_OFFSET = '0';

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
            combTable[i][j] = combTable[i - 1][j - 1] + combTable[i - 1][j];

    // Set result (nCk)
    String result = combTable[n][k];

    // Heap Deallocation
    for (int i = n; i > -1; i--)
        delete[] combTable[i];
    delete[] combTable;

    // Return result (nCk)
    return result;
}

String operator+(String a, String b)
{
    size_t size_a = a.size();
    size_t size_b = b.size();
    size_t size_result = size_a > size_b ? size_a + 1 : size_b + 1; // size of result must be one larger than maximum size of operands (Because of the possibility of carry)
    String result(size_result, '0');

    unsigned short adder;
    bool carry=false;

    int i; // index

    for (i = 0; i < size_a && i < size_b; i++)
    {
        adder = (a[i] - CHAR_OFFSET) + (b[i] - CHAR_OFFSET);

        if (carry)
            ++adder;

        if (adder > 9)
            carry = true;
        else
            carry = false;

        if (carry)
            result[i] = adder % 10 + CHAR_OFFSET;
    }

    if(size_a > size_b)
    {
        while(i<size_a)
        {
            result[i] = (a[i] - CHAR_OFFSET) + carry;
            carry = false;
            ++i;
        }
    }
    else if(size_b > size_a)
    {
        while(i<size_b)
        {
            result[i] = (b[i] - CHAR_OFFSET) + carry;
            carry = false;
            ++i;
        }
    }
    
    result[i] = carry+CHAR_OFFSET;
    if(result[i] == '0')
        result[i] = NULL;
        
    return result;
}

int main()
{
    int n, k;
    while (true)
    {
        std::cin >> n >> k;
        if(n==-1)
            break;
        std::cout << get_binomial_coefficient(n, k) << '\n';
    }
}
