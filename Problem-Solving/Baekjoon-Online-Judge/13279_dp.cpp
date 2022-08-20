/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/959 (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/13279

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>

// Namespace & Aliases
using namespace std;
typedef long long INT;

// Constants
const size_t MAX = 30000;  // The maximum size of sequence
const int MOD    = 100003; // Modulo number

// Global Variables
INT N;               // The number of numbers
INT A[MAX + 1];      // The sequence of numbers
INT dp[MAX + 1];     // The sequence for dynamic programminf
INT answer[MAX + 1]; // The sequence of answers

// Function Prototypes
void get_input();
void run();
void set_output();
void deallocate();
int main();

/*
 *  Function Name : get_input
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Getting data and store it in the appropriate data structures
 */
void get_input()
{
    // C++ Fast I/O Mechanism
    // https://dad-rock.tistory.com/737 (Korean)
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    for (size_t i = 1; i < N + 1; i++)
    {
        cin >> A[i];

        dp[i] = A[i];

        answer[1] += A[i];
        if (answer[1] > MOD - 1)
            answer[1] -= MOD;
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
    for (size_t i = 2; i < N + 1; i++)
    {
        int partial_sum = 0;

        for (size_t j = 1; j <= N - i + 1; j++)
        {
            partial_sum += dp[j];
            if (partial_sum > MOD - 1)
                partial_sum -= MOD;

            answer[i] += partial_sum * A[i + j - 1] % MOD;
            if (answer[i] > MOD - 1)
                answer[i] -= MOD;

            dp[j] = partial_sum * A[i + j - 1] % MOD;
        }

#ifdef DEBUG_MODE
        cout << "dp: ";
        for (size_t i = 1; i <= N; i++)
            cout << dp[i] << ' ';
        cout << '\n';
#endif
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
    INT Q;
    cin >> Q;

    INT K;
    while(Q--)
    {
        cin >> K;
        cout << answer[K] << '\n';
    }

#ifdef DEBUG_MODE
    cout << "\nAnswer: ";
    for (size_t i = 1; i <= N; i++)
        cout << answer[i] << ' ';
    cout << '\n';
#endif
}

/*
 *  Function Name : deallocate
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Deallocate the heap
 */
void deallocate()
{
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
    deallocate();

    return EXIT_SUCCESS;
}
