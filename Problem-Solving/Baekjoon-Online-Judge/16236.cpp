/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/797 (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/16236

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <queue>
#include <vector>
#include <string.h>

// Namespace & Aliases
using namespace std;
typedef int INDEX;
typedef pair<INDEX, INDEX> coor; // Symbol of type of coordinate

// Constants
const INDEX EMPTY = 0;                                                        // Symbol of empty space
const INDEX BABY_SHARK = 9;                                                   // Symbol of current position of baby shark
const INDEX MAX_N = 20;                                                       // Maximum size of board
const int DIRECTIONS = 4;                                                  // # of directions possible
const int DIRECTION[DIRECTIONS][2] = {{-1, 0}, {0, -1}, {0, +1}, {+1, 0}}; // Up, Left, Right, Down (Comply with priority)
const pair<coor, INDEX> ERROR = {{-1, -1}, 0};

// Global Variables
INDEX N;                   // Size of board
INDEX board[MAX_N][MAX_N]; // Board (Map)
INDEX baby_shark = 2;      // Current size of baby shark
int opt_seconds = 0;    // Time to eat all feeds ASAP (ANSWER)

// Function Prototypes
struct compare;
INDEX scan();
pair<coor, INDEX> get_nearest_feed();
coor get_baby_shark_pos();
bool is_valid_range(coor coor);
void get_input();
void run();
void set_output();
void deallocate();
int main();

// For sorting with heap(priority queue)
struct compare
{
    bool operator()(const pair<coor, INDEX> a, const pair<coor, INDEX> b)
    {
        if (a.first.first != b.first.first)
            return a.first.first > b.first.first;
        else
            return a.first.second > b.first.second;
    }
};

/*
 *  Function Name : scan
 *  Parameters    : -
 *  Return Type   : unsigned int
 *  Description   : It returns the number of feed that baby shark can eat currently
 */
INDEX scan()
{
    INDEX cnt_eatable = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] < baby_shark && board[i][j] != EMPTY && board[i][j] != BABY_SHARK)
                cnt_eatable++;
        }
    }

    return cnt_eatable;
}

/*
 *  Function Name : get_nearest_feed
 *  Parameters    : -
 *  Return Type   : pair<pair<INDEX, INDEX>, INDEX>
 *  Description   : It returns the coordinate and distance of the nearest feed the baby shark can eat
 */
pair<coor, INDEX> get_nearest_feed()
{
    pair<coor, INDEX> nearest;
    vector<pair<coor, INDEX>> nearset_coors;

    queue<pair<coor, INDEX>> bfs_queue;
    priority_queue<pair<coor, INDEX>, vector<pair<coor, INDEX>>, compare> same_dist_coors;
    bool check[MAX_N][MAX_N];
    memset(check, false, sizeof(bool) * MAX_N * MAX_N);

    coor baby_pos = get_baby_shark_pos();
    INDEX dist = 0;
    bfs_queue.push({baby_pos, dist});
    check[baby_pos.first][baby_pos.second] = true;
    while (!bfs_queue.empty())
    {
        coor curr_pos = bfs_queue.front().first;
        INDEX curr_dist = bfs_queue.front().second;
        bfs_queue.pop();

        if (board[curr_pos.first][curr_pos.second] != EMPTY && board[curr_pos.first][curr_pos.second] != BABY_SHARK && board[curr_pos.first][curr_pos.second] < baby_shark)
        {
            if (same_dist_coors.empty() || same_dist_coors.top().second == curr_dist)
            {
#ifdef DEBUG_MODE
                cout << "Push: <" << curr_pos.first << ", " << curr_pos.second << ">\n";
#endif
                nearest.first.first = curr_pos.first;
                nearest.first.second = curr_pos.second;
                nearest.second = curr_dist;
                same_dist_coors.push(nearest);
            }
        }

        for (int i = 0; i < DIRECTIONS; i++)
        {
            int next_x = curr_pos.first + DIRECTION[i][0];
            int next_y = curr_pos.second + DIRECTION[i][1];
            if (is_valid_range({next_x, next_y}))
            {
                if (!check[next_x][next_y] && board[next_x][next_y] <= baby_shark)
                {
                    bfs_queue.push({{next_x, next_y}, curr_dist + 1});
                    check[next_x][next_y] = true;
                }
            }
        }
    }

#ifdef DEBUG_MODE
    cout << "Top: <" << same_dist_coors.top().first.first << ", " << same_dist_coors.top().first.second << ">\n";
#endif

    if (same_dist_coors.empty())
        return ERROR;

    nearest = same_dist_coors.top();
    return nearest;
}

/*
 *  Function Name : get_baby_shark_pos
 *  Parameters    : -
 *  Return Type   : pair<unsigned int, unsigned int>
 *  Description   : It returns the coordinate of baby shark position in the board
 */
coor get_baby_shark_pos()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == BABY_SHARK)
                return {i, j};
        }
    }

    // Error
    throw "Can not find the position of baby shark";
}

/*
 *  Function Name : is_valid_range
 *  Parameters    : coor (pair<unsigned int, unsigned int>) : Coordinate pair consisting X and Y coordinates
 *  Return Type   : bool
 *  Description   : Determine whether the x-coordinate and y-coordinate are within the valid range of the board
 */
bool is_valid_range(coor coor)
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
    pair<coor, INDEX> feed;
    INDEX cnt_eat = 0;
    INDEX cnt_eatable = scan();
    coor baby_shark_pos;

    opt_seconds = 0;
    while (cnt_eatable > 0)
    {
        // Search
        feed = get_nearest_feed();
        baby_shark_pos = get_baby_shark_pos();

        if (feed.first.first == -1)
            break;

        // Move
        board[baby_shark_pos.first][baby_shark_pos.second] = EMPTY;
        board[feed.first.first][feed.first.second] = BABY_SHARK;

        // Eat
        cnt_eat++;
        cnt_eatable--;
        opt_seconds += feed.second;
        if (cnt_eat == baby_shark)
        {
            cnt_eat = 0;
            baby_shark++;
            cnt_eatable = scan();
        }

#ifdef DEBUG_MODE
        cout << "Current board state:\n";
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << board[i][j] << ' ';
            cout << '\n';
        }
        cout << "Movement: " << feed.second << '\n';
        cout << "Total movement: " << opt_seconds << '\n';
        cout << "Level of baby shark: " << baby_shark << "\n\n";
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
    cout << opt_seconds << '\n';
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
