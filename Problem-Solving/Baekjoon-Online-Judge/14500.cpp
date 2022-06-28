/* 
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/918 (Korean)
 * 
 */ 

// Problem URL
// https://www.acmicpc.net/problem/14500

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <algorithm>
#include <vector>

// Namespace & Aliases
using namespace std;
typedef unsigned int ui;

// Constants
const ui MAX = 500; // Maximum size of board

// Global Variables
ui board[MAX][MAX]; // Board
ui N = 0;           // Height of board
ui M = 0;           // Width of board
ui max_type1 = 0;   // Maximum value of type 1 case
ui max_type2 = 0;   // Maximum value of type 2 case
ui max_type3 = 0;   // Maximum value of type 3 case
ui max_type4 = 0;   // Maximum value of type 4 case
ui max_type5 = 0;   // Maximum value of type 5 case

// Function Prototypes
void get_input();
void run();
void set_output();
void deallocate();
int main();

bool is_valid_range(pair<ui, ui> coor);
vector<pair<ui, ui>> set_coors(pair<ui, ui> coor1, pair<ui, ui> coor2,pair<ui, ui> coor3,pair<ui, ui> coor4);
ui calc_sum(vector<pair<ui, ui>> coors);
ui get_max_type1();
ui get_max_type2();
ui get_max_type3();
ui get_max_type4();
ui get_max_type5();

/*
 *  Function Name : get_input
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Getting data and store it in the appropriate data structures
 */
void get_input()
{
    // C++ Fast I/O Mechanism
    // https://dad-rock.tistory.com/737?category=723623 (Korean)
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
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
    max_type1 = get_max_type1();
    max_type2 = get_max_type2();
    max_type3 = get_max_type3();
    max_type4 = get_max_type4();
    max_type5 = get_max_type5();
}

/*
 *  Function Name : set_output
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Setting the output
 */
void set_output()
{
#ifndef DEBUG_MODE
    cout << max({max_type1, max_type2, max_type3, max_type4, max_type5}) << '\n';
#endif

#ifdef DEBUG_MODE
    cout << "Max of Type 1 = " << max_type1 << '\n';
    cout << "Max of Type 2 = " << max_type2 << '\n';
    cout << "Max of Type 3 = " << max_type3 << '\n';
    cout << "Max of Type 4 = " << max_type4 << '\n';
    cout << "Max of Type 5 = " << max_type5 << '\n';
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

/*
 *  Function Name : is_valid_range
 *  Parameters    : 1) coor (pair<unsigned int, unsigned int>) : Coordinate pair consisting X and Y coordinates
 *  Return Type   : bool
 *  Description   : Determine whether the x-coordinate and y-coordinate are within the valid range of the board
 */
bool is_valid_range(pair<ui, ui> coor)
{
    return ((coor.first < N) && (coor.second < M));
}

/*
 *  Function Name : set_coors
 *  Parameters    : 1) coor1 (pair<unsigned int, unsigned int>) : Coordinate pair consisting X and Y coordinates
 *                  2) coor2 (pair<unsigned int, unsigned int>) : Coordinate pair consisting X and Y coordinates
 *                  3) coor3 (pair<unsigned int, unsigned int>) : Coordinate pair consisting X and Y coordinates
 *                  4) coor4 (pair<unsigned int, unsigned int>) : Coordinate pair consisting X and Y coordinates
 *  Return Type   : vector<pair<ui, ui>>
 *  Description   : If the 4 coordinate pairs are within a valid range,
 *                  it returns a vector storing them
 *                  Otherwise, it returns empty vector
 */
vector<pair<ui, ui>> set_coors(pair<ui, ui> coor1, pair<ui, ui> coor2,pair<ui, ui> coor3,pair<ui, ui> coor4)
{
    vector<pair<ui, ui>> coors;

    if(is_valid_range(coor1) && is_valid_range(coor2) && is_valid_range(coor3) && is_valid_range(coor4))
    {
        coors.push_back(coor1);
        coors.push_back(coor2);
        coors.push_back(coor3);
        coors.push_back(coor4);
    }
    else
        coors.clear();

    return coors;
}

/*
 *  Function Name : calc_sum
 *  Parameters    : 1) coors (vector<pair<unsigned int, unsigned int>>) : Vector with coordinate pairs stored
 *  Return Type   : unsigned int
 *  Description   : Returns the sum of scores corresponding to all coordinates stored in coors
 */
ui calc_sum(vector<pair<ui, ui>> coors)
{
    ui sum = 0;

    while (!coors.empty())
    {
        sum += board[coors.back().first][coors.back().second];
        coors.pop_back();
    }

    return sum;
}

/*
 *  Function Name : get_max_type1
 *  Parameters    : -
 *  Return Type   : unsigned int
 *  Description   : Returns the maximum score for tetromino of type below:
 *                  Type: ㅁㅁㅁㅁ
 */
ui get_max_type1()
{
    ui curr_max = 0;
    vector<pair<ui, ui>> coors; // Coordinates

    /*
    Detailed Type: ㅁㅁㅁㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j}, {i, j+1}, {i, j+2}, {i, j+3});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    /*
    Detailed Type: ㅁ
                   ㅁ
                   ㅁ
                   ㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j}, {i+1, j}, {i+2, j}, {i+3, j});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    return curr_max;
}

/*
 *  Function Name : get_max_type2
 *  Parameters    : -
 *  Return Type   : unsigned int
 *  Description   : Returns the maximum score for tetromino of type below:
 *                  Type: ㅁㅁㅁ
 *                            ㅁ
 */
ui get_max_type2()
{
    ui curr_max = 0;
    vector<pair<ui, ui>> coors; // Coordinates

    /*
    Detailed Type: ㅁㅁㅁ
                       ㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j}, {i, j+1}, {i, j+2}, {i+1, j+2});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    /*
    Detailed Type:     ㅁ
                   ㅁㅁㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j+2}, {i+1, j}, {i+1, j+1}, {i+1, j+2});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    /*
    Detailed Type: ㅁㅁㅁ
                   ㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j}, {i, j+1}, {i, j+2}, {i+1, j});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));            
        }
    }

    /*
    Detailed Type: ㅁ
                   ㅁㅁㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j}, {i+1, j}, {i+1, j+1}, {i+1, j+2});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    /*
    Detailed Type: ㅁㅁ
                     ㅁ
                     ㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j}, {i, j+1}, {i+1, j+1}, {i+2, j+1});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    /*
    Detailed Type: ㅁㅁ
                   ㅁ
                   ㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j}, {i, j+1}, {i+1, j}, {i+2, j});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    /*
    Detailed Type:   ㅁ
                     ㅁ
                   ㅁㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j+1}, {i+1, j+1}, {i+2, j}, {i+2, j+1});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    /*
    Detailed Type: ㅁ
                   ㅁ
                   ㅁㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j}, {i+1, j}, {i+2, j}, {i+2, j+1});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    return curr_max;
}

/*
 *  Function Name : get_max_type3
 *  Parameters    : -
 *  Return Type   : unsigned int
 *  Description   : Returns the maximum score for tetromino of type below:
 *                  Type: ㅁㅁ
 *                          ㅁㅁ
 */
ui get_max_type3()
{
    ui curr_max = 0;
    vector<pair<ui, ui>> coors; // Coordinates

    /*
    Detailed Type: ㅁㅁ
                     ㅁㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j}, {i, j+1}, {i+1, j+1}, {i+1, j+2});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    /*
    Detailed Type:   ㅁㅁ
                   ㅁㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j+1}, {i, j+2}, {i+1, j}, {i+1, j+1});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    /*
    Detailed Type:   ㅁ
                   ㅁㅁ
                   ㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j+1}, {i+1, j}, {i+1, j+1}, {i+2, j});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    /*
    Detailed Type: ㅁ
                   ㅁㅁ
                     ㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j}, {i+1, j}, {i+1, j+1}, {i+2, j+1});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    return curr_max;
}

/*
 *  Function Name : get_max_type4
 *  Parameters    : -
 *  Return Type   : unsigned int
 *  Description   : Returns the maximum score for tetromino of type below:
 *                  Type: ㅁㅁㅁ
 *                          ㅁ
 */
ui get_max_type4()
{
    ui curr_max = 0;
    vector<pair<ui, ui>> coors; // Coordinates

    /*
    Detailed Type: ㅁㅁㅁ
                     ㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j}, {i, j+1}, {i, j+2}, {i+1, j+1});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    /*
    Detailed Type:   ㅁ
                   ㅁㅁㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j+1}, {i+1, j}, {i+1, j+1}, {i+1, j+2});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    /*
    Detailed Type:  ㅁ
                  ㅁㅁ
                    ㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j+1}, {i+1, j}, {i+1, j+1}, {i+2, j+1});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    /*
    Detailed Type:ㅁ
                  ㅁㅁ
                  ㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j}, {i+1, j}, {i+1, j+1}, {i+2, j});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    return curr_max;
}

/*
 *  Function Name : get_max_type4
 *  Parameters    : -
 *  Return Type   : unsigned int
 *  Description   : Returns the maximum score for tetromino of type below:
 *                  Type: ㅁㅁ
 *                        ㅁㅁ
 */
ui get_max_type5()
{
    ui curr_max = 0;
    vector<pair<ui, ui>> coors; // Coordinates

    /*
    Detailed Type: ㅁㅁ
                   ㅁㅁ
    */
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            coors.clear();
            coors = set_coors({i, j}, {i, j+1}, {i+1, j}, {i+1, j+1});

            if(coors.empty())
                continue; 

            curr_max = max(curr_max, calc_sum(coors));
        }
    }

    return curr_max;
}
