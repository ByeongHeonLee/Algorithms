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

// Namespace & Aliases
using namespace std;
typedef unsigned int INT;

// Constants
const int MAX         = 10000; // The maximum number of jobs
const INT PREDECESSOR = 101;   // The Symbol of Predecessor

// Global Variables
INT N;               // The Number of Jobs
INT* graph[MAX+1];   // 2-D Array for Graph
INT opt_times[MAX];  // 1-D Array for Optimal Turnaround Time

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

    for (int i = 1; i < N + 1; i++)
    {
        opt_times[i] = 0;

        graph[i] = new INT[i+1];
        for (int j = 1; j < i + 1; j++)
            graph[i][j] = 0;
    }

    INT turnaround_time, cnt_predecessor, predecessor;
    for (int i = 1; i < N + 1; i++)
    {
        cin >> turnaround_time >> cnt_predecessor;

        graph[i][i] = turnaround_time;

        while (cnt_predecessor--)
        {
            cin >> predecessor;
            graph[i][predecessor] = PREDECESSOR;
        }
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
    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < i + 1; j++)
        {
            if (graph[i][j] == PREDECESSOR)
                opt_times[i] = max(opt_times[i], opt_times[j]);
        }

        opt_times[i] += graph[i][i];
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
cout << "STATUS: graph\n";
    for (int i = 1; i < N + 1; i++)
    {
        for(int j=1;j<N+1;j++)
            cout << setw(3) << graph[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';

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
    for (int i = 1; i < N + 1; i++)
        delete[] graph[i];
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
