/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/923 (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/10026

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <queue>

// Namespace & Aliases
using namespace std;
typedef int INT;

// Constants
const int MAX = 100;
const char CHECK_SIGN = 'X';
const int DIRECTIONS = 4;
const int DIRECTION[4][2] = {{-1, 0}, {+1, 0}, {0, -1}, {0, +1}}; // Up - Down, Left - Right

// Global Variables
char board[MAX][MAX];
int N;
int R_blocks = 0;
int G_blocks = 0;
int B_blocks = 0;

// Function Prototypes
void convert_R_to_G(int n);
bool is_valid_area(pair<int, int> coor, int n);
void get_input();
void run();
void set_output();
void deallocate();
int main();

/*
 *  Function Name : convert_R_to_G
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : It changes the board by turning red to green,
 *                  meaning red and green are the same colors (as color blindness)
 */
void convert_R_to_G()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == 'R')
                board[i][j] = 'G';
        }
    }
}

/*
 *  Function Name : is_valid_area
 *  Parameters    : coor (pair<int, int>) : 2-dimensional coordinate
 *  Return Type   : bool
 *  Description   : It is determined whether the 2-dimensional coordinate(coor) is within a valid range
 */
bool is_valid_area(pair<int, int> coor)
{
    return (-1 < coor.first && coor.first < N && -1 < coor.second && coor.second < N);
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
    // https://dad-rock.tistory.com/737 (Korean)
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cin >> board[i][j];
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
    char check[MAX][MAX];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            check[i][j] = board[i][j];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (check[i][j] != CHECK_SIGN)
            // BFS
            {
                queue<pair<int, int>> q;
                q.push({i, j});
                char curr_color = check[i][j];

                while (!q.empty())
                {
                    int curr_x = q.front().first;
                    int curr_y = q.front().second;
                    check[curr_x][curr_y] = CHECK_SIGN;
                    q.pop();

                    for (int dir = 0; dir < DIRECTIONS; dir++)
                    {
                        int next_x = curr_x + DIRECTION[dir][0];
                        int next_y = curr_y + DIRECTION[dir][1];

                        if (is_valid_area({next_x, next_y}) && check[next_x][next_y] == curr_color)
                        {
                            q.push({next_x, next_y});
                            check[next_x][next_y] = CHECK_SIGN;
                        }
                    }
                }

                if (curr_color == 'R')
                    R_blocks++;
                else if (curr_color == 'G')
                    G_blocks++;
                else if (curr_color == 'B')
                    B_blocks++;
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
    cout << R_blocks + G_blocks + B_blocks << ' ';
}

/*
 *  Function Name : deallocate
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Deallocate the heap
 */
void deallocate()
{
    R_blocks = G_blocks = B_blocks = 0;
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

    // Run as normal
    run();
    set_output();
    deallocate();

    // Convert from normal to color blindness
    convert_R_to_G();

    // Run as color blindness
    run();
    set_output();
    deallocate();

    return EXIT_SUCCESS;
}
