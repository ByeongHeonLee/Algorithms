/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/954 (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/2056

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

// Namespace & Aliases
using namespace std;
typedef unsigned int INT;

// Constants
const int MAX = 10000;       // The maximum number of jobs
const INT PREDECESSOR = 101; // The symbol of predecessor

// Global Variables
INT N;                             // The number of jobs
INT job_times[MAX + 1];            // 1-D array to store turnaround times
vector<INT> predecessors[MAX + 1]; // Vector to store information of predecessor
INT opt_times[MAX + 1];            // 1-D array for optimal turnaround time

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

    INT turnaround_time, cnt_predecessor, predecessor;
    for (int i = 1; i < N + 1; i++)
    {
        cin >> turnaround_time >> cnt_predecessor;

        job_times[i] = turnaround_time;

        while (cnt_predecessor--)
        {
            cin >> predecessor;
            predecessors[i].push_back(predecessor);
        }
    }

#ifdef DEBUG_MODE
    cout << "STATUS: job times & predecessors\n";
    for (int i = 1; i < N + 1; i++)
    {
        cout << "Turnaround time of " << i << "th Job: " << job_times[i] << '\n';

        cout << "Predecessor: ";
        vector<INT>::iterator iter = predecessors[i].begin();
        for (iter; iter < predecessors[i].end(); iter++)
            cout << *iter << ' ';
        cout << "\n\n";
    }

    cout << "\n\n";
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
    for (int i = 1; i < N + 1; i++)
    {
        while (!predecessors[i].empty())
        {
            opt_times[i] = max(opt_times[i], opt_times[predecessors[i].back()]);
            predecessors[i].pop_back();
        }

        opt_times[i] += job_times[i];
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
#ifdef DEBUG_MODE
    cout << "STATUS: opt_times\n";
    for (int i = 1; i < N + 1; i++)
        cout << opt_times[i] << ' ';
    cout << "\n\n";
    cout << "Answer:\n";
#endif

    INT optimal_times = 0;

    for (int i = 1; i < N + 1; i++)
        optimal_times = max(optimal_times, opt_times[i]);

    cout << optimal_times << '\n';
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
