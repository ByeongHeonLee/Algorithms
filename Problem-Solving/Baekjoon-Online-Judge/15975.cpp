/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * (Blog Post URL) (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/15975

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

// Namespace & Aliases
using namespace std;
typedef int SIZE;

// Constants
const SIZE COORS = 100000 + 1; // Maximum # of coordinates

// Global Variables
vector<SIZE> coor[COORS];         // Vector for coordinates
SIZE N;                           // # of coordinates
SIZE COLORS = 0;                  // # of colors
unsigned long long sum_arrow = 0; // Sum of all of arrow's length

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

    SIZE coordinate, color;
    for (int i = 0; i < N; i++)
    {
        cin >> coordinate >> color;
        coor[color].push_back(coordinate);
        COLORS = max(COLORS, color);
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
#ifdef DEBUG_MODE
    cout << "[Before sorting]" << '\n';
    for (int i = 1; i <= COLORS; i++)
    {
        cout << "Color : " << i << " (" << coor[i].size() << " Points)\n";

        for (int j = 0; j < coor[i].size(); j++)
            cout << coor[i][j] << ' ';

        cout << '\n';
    }
#endif

    for (int i = 1; i <= COLORS; i++)
    {
        if (coor[i].size() > 1)
            sort(coor[i].begin(), coor[i].end());
    }

#ifdef DEBUG_MODE
    cout << "[After sorting]" << '\n';
    for (int i = 1; i <= COLORS; i++)
    {
        cout << "Color : " << i << " (" << coor[i].size() << " Points)\n";

        for (int j = 0; j < coor[i].size(); j++)
            cout << coor[i][j] << ' ';

        cout << '\n';
    }
#endif

    for (int i = 1; i <= COLORS; i++)
    {
        if (coor[i].size() < 2)
            continue;

        for (int j = 0; j < coor[i].size(); j++)
        {
            // at Start point
            if (j == 0)
                sum_arrow += coor[i][j + 1] - coor[i][j];
            // at End point
            else if (j == coor[i].size() - 1)
                sum_arrow += coor[i][j] - coor[i][j - 1];
            // at Middle Point
            else
            {
                SIZE prev = coor[i][j - 1];
                SIZE curr = coor[i][j];
                SIZE next = coor[i][j + 1];
                sum_arrow += curr - prev < next - curr ? curr - prev : next - curr;
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
    cout << sum_arrow << '\n';
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
