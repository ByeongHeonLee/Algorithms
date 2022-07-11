/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * (Blog Post URL) (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/1932

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <algorithm>
#include <string.h>

// Namespace & Aliases
using namespace std;
typedef int SIZE;

// Constants
const SIZE MAX = 500; // Maximum size of input triangle

// Global Variables
SIZE triangle[MAX][MAX]; // Array to store triangle
SIZE optimum[MAX][MAX];  // Arrat to store optimal value
SIZE n;                  // Size of triangle

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

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            cin >> triangle[i][j];
            optimum[i][j] = 0;
        }
    }

#ifdef DEBUG_MODE
    cout << "[Status: triangle]\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i + 1; j++)
            cout << triangle[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
#endif
}

/*
 *  Function Name : run
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Main Logic
 */
void run()
{
    optimum[0][0] = triangle[0][0];

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            if (j == 0)
                optimum[i][j] += optimum[i - 1][0] + triangle[i][j];
            else if (j == i)
                optimum[i][j] += optimum[i - 1][i - 1] + triangle[i][j];
            else
                optimum[i][j] = max(optimum[i - 1][j - 1], optimum[i - 1][j]) + triangle[i][j];
        }
    }

#ifdef DEBUG_MODE
    cout << "[Status: optimum]\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i + 1; j++)
            cout << optimum[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
#endif
}

/*
 *  Function Name : set_output
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Setting the output
 */
void set_output()
{
    SIZE max_cost = 0;

    for (int i = 0; i < n; i++)
        max_cost = max(max_cost, optimum[n - 1][i]);

    cout << max_cost << '\n';
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
