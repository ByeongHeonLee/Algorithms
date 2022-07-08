/* 
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * (Blog Post URL) (Korean)
 * 
 */ 

// Problem URL
// https://www.acmicpc.net/problem/2822

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <algorithm>
#include <vector>

// Namespace & Aliases
using namespace std;
typedef unsigned short INT;

// Constants
const INT SCORES = 8; // # of scores

// Global Variables
pair<INT, INT> score[SCORES]; // Array to store <score, sequence> pairs
INT score_idx[SCORES];        // Array to store sequences that applied sum_scores
INT sum_scores = 0;           // Sum of the large scores from 1st to 5th

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

    for(int i=0;i<SCORES;i++){
        cin >> score[i].first;
        score[i].second = i+1;
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
    sort(score, score+SCORES);

    for(int i=3;i<SCORES;i++)
    {
        sum_scores += score[i].first;
        score_idx[i-3] = score[i].second;
    }

    sort(score_idx, score_idx+5);
}

/*
 *  Function Name : set_output
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Setting the output
 */
void set_output()
{
    cout << sum_scores << '\n';

    for(int i=0;i<SCORES-3;i++)
        cout << score_idx[i] << ' ';

    cout << '\n';
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
