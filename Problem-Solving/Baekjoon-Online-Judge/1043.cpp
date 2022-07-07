/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/930 (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/1043

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <vector>
#include <set>

// Namespace & Aliases
using namespace std;
typedef short INT;

// Constants

// Global Variables
INT N;
INT M;
set<INT> truth;
vector<vector<INT>> party;

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

    cin >> N >> M;
    vector<vector<INT>> temp(M);
    party = temp;

    INT num;
    cin >> num;

    int p;
    for (int i = 0; i < num; i++)
    {
        cin >> p;
        truth.insert(p);
    }

    for (int i = 0; i < M; i++)
    {
        cin >> num;
        for (int j = 0; j < num; j++)
        {
            cin >> p;
            party[i].push_back(p);
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
    for (int x = 0; x < M; x++)
    { // 최대 M번 훑기

        int i = 0;
        bool flag = false;

        for (; i < party.size(); i++)
        {

            for (int k = 0; k < party[i].size(); k++)
            {

                if (truth.find(party[i][k]) != truth.end())
                {
                    flag = true;
                    break;
                }
            }
            if (flag)
            {
                for (int k = 0; k < party[i].size(); k++)
                {
                    truth.insert(party[i][k]);
                }
                break;
            }
        }
        if (flag)
            party.erase(party.begin() + i);
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
    cout << party.size() << '\n';
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
