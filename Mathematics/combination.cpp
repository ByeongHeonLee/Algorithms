// Namespace & Aliases
typedef long long INT;

/*
 *  Function Name : get_binomial_coefficient
 *  Parameters    : 1) n (int) : # of total elements (Set)
 *                  2) k (int) : # of distinct elements (Subset)
 *  Return Type   : INT (Any integer type, depends on programmer)
 *  Description   : Return the result value of n choose k (nCk)
 */
INT get_binomial_coefficient(int n, int k) {

    // Heap Allcation
    INT **combTable = new INT *[n + 1];
    for (int i = 0; i < n + 1; i++)
    {
        combTable[i] = new INT[n + 1];
        combTable[i][0] = 1; // nC0 = 1
        combTable[i][i] = 1; // nCn = 1
    }

    k = (n - k > k) ? k : n - k; // nCk = nCn-k (short cut)

    // Calculation based on formula: nCk = n-1Ck-1 + n-1Ck
    for (int i = 2; i < n + 1; i++)
        for (int j = 1; j < i && j <= k; j++)
            combTable[i][j] = combTable[i - 1][j - 1] + combTable[i - 1][j];

    INT result = combTable[n][k];

    // Heap Deallocation
    for (int i = n; i > -1; i--)
        delete[] combTable[i];
    delete[] combTable;

    // Exception handling
    if(result < 0)
        throw "Exception: Overflow occurred for internal data type";

    return result;
}