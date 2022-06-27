/* 
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/343 (Korean)
 */ 

// Problem URL
// https://www.acmicpc.net/problem/1010

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>

// Namespace & Aliases
using namespace std;
typedef long long INT;

// Global Variables
INT** input_pairs = nullptr;
int reps = 0;

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

    return result;
}

/*
 *  Function Name : get_input
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Getting data and store it in the appropriate data structures
 */
void get_input()
{
    // C++ Fast I/O Mechanism
    // https://dad-rock.tistory.com/737?category=723623 (Korean)
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> reps;

    input_pairs = new INT* [reps];
    
    for (int i = 0; i < reps; i++)
		input_pairs[i] = new INT[3];

    for (int i = 0; i < reps;i++) {
		int N, M;
		std::cin >> N >> M;
		input_pairs[i][0] = M;
		input_pairs[i][1] = N;
    }
}

/*
 *  Function Name : run
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Main Logic
 */
void run()
{
    int n, k;
    for (int i = 0; i < reps;i++){
        n = input_pairs[i][0];
        k = input_pairs[i][1];
		input_pairs[i][2] = get_binomial_coefficient(n, k);
    }
}

/*
 *  Function Name : set_output
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Setting the output
 */
void set_output()
{
    for (int i = 0; i < reps;i++)
		cout << input_pairs[i][2] << '\n';
}

/*
 *  Function Name : deallocate
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Deallocate the heap
 */
void deallocate()
{
    for (int i = 0; i < reps; i++)
		delete[] input_pairs[i];
	delete[] input_pairs;	
}

/*
 *  Function Name : main
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Main Function
 */
int main()
{
    get_input();
    run();
    set_output();

    return EXIT_SUCCESS;
}
