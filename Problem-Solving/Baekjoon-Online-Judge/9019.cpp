/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/929 (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/9019

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <queue>   // queue Class
#include <string>  // string Class
#include <cstring> // memset()

// Namespace & Aliases
using namespace std;

// Constants
const int MAX = 10000;

// Global Variables
int T; // # of test cases
bool checked[MAX];
int input;
int target;

// Function Prototypes
int D(int input);
int S(int input);
int L(int input);
int R(int input);
void search(int input, int target);
void get_input();
void run();
void set_output();
void deallocate();
int main();

/*
 *  Function Name : D
 *  Parameters    : input (int) : Value to apply Operation D
 *  Return Type   : int
 *  Description   : It returns a result of Operation D
 */
int D(int input)
{
    return input * 2 % 10000;
}

/*
 *  Function Name : S
 *  Parameters    : input (int) : Value to apply Operation S
 *  Return Type   : int
 *  Description   : It returns a result of Operation S
 */
int S(int input)
{
    if (input == 0)
        return 9999;
    return input - 1;
}

/*
 *  Function Name : L
 *  Parameters    : input (int) : Value to apply Operation L
 *  Return Type   : int
 *  Description   : It returns a result of Operation L
 */
int L(int input)
{
    if (input == 0)
        return 0;

    return input % 1000 * 10 + input / 1000;
}

/*
 *  Function Name : R
 *  Parameters    : input (int) : Value to apply Operation R
 *  Return Type   : int
 *  Description   : It returns a result of Operation R
 */
int R(int input)
{
    if (input == 0)
        return 0;

    int lsb = input % 10;
    return input % 10 * 1000 + input / 10;
}

/*
 *  Function Name : search
 *  Parameters    : curr_value   (int) : Current value
 *                  target_value (int) : Target value
 *  Return Type   : -
 *  Description   : It operates BFS to calculate minimum cost to find target_value
 */
void search(int curr_value, int target_value)
{
    queue<pair<int, string>> q;
    q.push({curr_value, ""});

    while (!q.empty())
    {
        pair<int, string> node = q.front();
        q.pop();

        int post_d= D(node.first);
        int post_s= S(node.first);
        int post_l= L(node.first);
        int post_r= R(node.first);

        if(node.first == target_value){
            cout << node.second << '\n';
            return;
        }
        else if (post_d == target_value)
        {
            cout << node.second + 'D' << '\n';
            return;
        }
        else if (post_s == target_value)
        {
            cout << node.second + 'S' << '\n';
            return;
        }
        else if (post_l == target_value)
        {
            cout << node.second + 'L' << '\n';
            return;
        }
        else if (post_r == target_value)
        {
            cout << node.second + 'R' << '\n';
            return;
        }

        checked[node.first] = true;

        if (node.first != 0 && !checked[post_d]){
            q.push({post_d, node.second + 'D'});
            checked[post_d] = true;
        }

        if(!checked[post_s]){
            q.push({post_s, node.second + 'S'});
            checked[post_s] = true;
        }

        if (node.second.back() != 'R' && !checked[post_l]){
            q.push({post_l, node.second + 'L'});
            checked[post_l] = true;
        }

        if (node.second.back() != 'L' && !checked[post_r]){
            q.push({post_r, node.second + 'R'});
            checked[post_r] = true;
        }
    }
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

    memset(checked, false, sizeof(bool) * MAX);

    cin >> input >> target;
}

/*
 *  Function Name : run
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Main Logic
 */
void run()
{
    search(input, target);
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
    cin >> T;
    while (T--)
    {
        get_input();
        run();
    }

    return EXIT_SUCCESS;
}
