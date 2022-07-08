/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * (Blog Post URL) (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/5800

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <algorithm>

// Namespace & Aliases
using namespace std;
typedef int INT;

// Constants
const INT MAX_CLASS = 100 + 1;
const INT MAX_STUDENT = 50 + 1;

// Global Variables
INT scores[MAX_CLASS][MAX_STUDENT]; // Vector to store scores
INT l_gaps[MAX_CLASS];              // Vector to store largest gap
INT classes;                        // # of classes

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

    INT students, score;
    cin >> classes;
    for (int i = 0; i < classes; i++)
    {
        cin >> scores[i][0];
        for (int j = 1; j <= scores[i][0]; j++)
            cin >> scores[i][j];

        sort(&scores[i][1], &scores[i][1] + scores[i][0]);
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
    INT l_gap;

    for (int i = 0; i < classes; i++)
    {
        l_gap = 0;

        for (int j = 1; j < scores[i][0]; j++)
        {
            INT prev = scores[i][j];
            INT next = scores[i][j+1];

            l_gap = max(l_gap, next-prev);
        }

        l_gaps[i] = l_gap;
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
    for (int i = 0; i < classes; i++)
    {
        cout << "Class " << i + 1 << '\n';

        cout << "Max " << scores[i][scores[i][0]] << ", ";
        cout << "Min " << scores[i][1] << ", ";
        cout << "Largest gap " << l_gaps[i] << '\n';
    }
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
