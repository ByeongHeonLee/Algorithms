/* 
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/926 (Korean)
 * 
 */ 

// Problem URL
// https://www.acmicpc.net/problem/16928

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <queue>

// Namespace & Aliases
using namespace std;
typedef unsigned int SIZE;

// Constants
const SIZE START = 1;          // Sign of start position in map
const SIZE END = 100;          // Sign of end position in map
const unsigned short DICE = 6; // # of cases come out from dice
const short UNVISITED = -1;    // Sign of unvisited

// Global Variables
SIZE N;             // # of ladders
SIZE M;             // # of snakes
SIZE cost[END + 1]; // Optimal cost to the number(index)
SIZE jump[END + 1]; // Board that has the next number(index)

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

    for (int i = START; i <= END; i++)
    {
        cost[i] = UNVISITED;
        jump[i] = i;
    }

    cin >> N >> M;

    int start_pos, end_pos;
    for (int i = 0; i < N + M; i++)
    {
        cin >> start_pos >> end_pos;
        jump[start_pos] = end_pos;
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
    SIZE curr_pos = START;
    SIZE next_pos;
    cost[curr_pos] = 0;

    queue<SIZE> q;
    q.push(curr_pos);
    while (!q.empty())
    {
        curr_pos = q.front();
        q.pop();

        for (int i = 1; i <= DICE; i++)
        {
            next_pos = curr_pos + i;

            if (next_pos > END)
                continue;

            next_pos = jump[next_pos];

            if (cost[next_pos] == UNVISITED)
            {
                cost[next_pos] = cost[curr_pos] + 1;
                q.push(next_pos);
            }
        }
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
    cout << cost[END] << '\n';
}

/*
 *  Function Name : deallocate
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Deallocate the heap
 */
void deallocate()
{}

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
