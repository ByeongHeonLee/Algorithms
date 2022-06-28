/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/920 (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/7576

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <queue>

// Namespace & Aliases
using namespace std;
typedef short INT;

// Constants
const size_t MAX_SIZE = 1000;                      // Maximum size of side of container
const short DIMENSION = 2;                         // 1D - 1, 2D - 2, 3D - 3
const short DIRECTION[2][2][2] = { {{0, -1}, {0, 1}},   // Left, Right
                                   {{1, 0}, {-1, 0}}};  // Front, Back

const short RIPE = 1;            // Sign of ripe tomato
const short UNRIPE = 0;          // Sign of unripe tomato
const short EMPTY = -1;          // Sign of empty
const short ALL_RIPE = 0;        // Sign that all tomatoes are ripe
const short NEVER_ALL_RIPE = -1; // Sign that all tomatoes can never be ripe

// Global Variables
INT container[MAX_SIZE][MAX_SIZE]; // Container for tomatoes
INT width, column;                 // Size of container
bool ALL_RIPE_FLAG = true;         // Falg about all tomatoes are ripe
queue<pair<INT, INT>> q;           // Queue for BFS

// Function Prototypes
void get_input();
void run();
void set_output();
void deallocate();
int main();

bool is_inside(pair<INT, INT> coor);

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

    cin >> width >> column;

    for (int y = 0; y < column; y++)
    {
        for (int x = 0; x < width; x++)
        {
            cin >> container[y][x];

            if (container[y][x] == RIPE)
                q.push({y, x});

            if (ALL_RIPE_FLAG && container[y][x] == UNRIPE)
                ALL_RIPE_FLAG = false;
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
    if (ALL_RIPE_FLAG)
    {
        cout << ALL_RIPE << '\n';
        return;
    }

    int days = 0;
    int curr_ripes = q.size();
    int next_ripes = 0;
    int cnt_curr_ripes = 0;

    short next_y, next_x;

    // Start BFS
    while (!q.empty())
    {
        pair<INT, INT> focus = q.front();
        q.pop();

        for (int d = 0; d < DIMENSION; d++)
        {
            for (int side = 0; side < 2; side++)
            {
                next_y = focus.first + DIRECTION[d][side][0];
                next_x = focus.second + DIRECTION[d][side][1];

                pair<short, short> next_coor = {next_y, next_x};

                if (is_inside(next_coor) && container[next_y][next_x] == UNRIPE)
                {
                    q.push(next_coor);
                    container[next_y][next_x] = RIPE;
                    next_ripes++;
                }
            }
        }

        cnt_curr_ripes++;
        if (cnt_curr_ripes == curr_ripes && !q.empty())
        {
            days++;
            curr_ripes = next_ripes;
            next_ripes = cnt_curr_ripes = 0;

#ifdef DEBUG_MODE
            cout << "Days : " << days << '\n';
            cout << "Size of q : " << q.size() << '\n';
            for (int y = 0; y < column; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    cout << container[y][x] << ' ';
                }
                cout << '\n';
            }
            cout << '\n';
#endif
        }
    }

    for (int y = 0; y < column; y++)
    {
        for (int x = 0; x < width; x++)
        {

            if (container[y][x] == UNRIPE)
            {
                cout << NEVER_ALL_RIPE << '\n';
                return;
            }
        }
    }

    cout << days << '\n';
}

/*
 *  Function Name : set_output
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Setting the output
 */
void set_output()
{
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

/*
 *  Function Name : main
 *  Parameters    : coor (pair<short, short>) : 2-dimensional coordinate
 *  Return Type   : bool
 *  Description   : It is determined whether the 2-dimensional coordinate(coor) is within a valid range.
 */
bool is_inside(pair<INT, INT> coor)
{
    INT y = coor.first;
    INT x = coor.second;

    return ((0 <= y && y < column) && (0 <= x && x < width));
}
