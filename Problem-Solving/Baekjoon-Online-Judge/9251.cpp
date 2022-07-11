/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/934 (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/9251

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>

// Namespace & Aliases
using namespace std;
typedef int INT;

// Constants
const int MAX = 1000+1; // Maximum number of characters that consist the input string

// Global Variables
string str1, str2;      // Input strings
int len_str1, len_str2; // Length of input strings
int lcs[MAX][MAX];      // Length of LCS for str1, str2

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

    cin >> str1 >> str2;
}

/*
 *  Function Name : run
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Main Logic
 */
void run()
{
    len_str1 = str1.size();
    len_str2 = str2.size();

    memset(lcs, 0, sizeof(int) * MAX * MAX);

    for (int i = 1; i <= len_str1; i++)
    {
        for (int j = 1; j <= len_str2; j++)
        {
            if (str1[i-1] == str2[j-1])
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            else
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
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
    cout << lcs[len_str1][len_str2] << '\n';
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
