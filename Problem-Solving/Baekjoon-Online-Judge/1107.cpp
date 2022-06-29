/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/921 (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/1107

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string.h>

// Namespace & Aliases
using namespace std;
typedef int CH;

// Constants
const CH MAX_CH = 1000000; // Accessible maximum channel
const CH CURR_CH = 100;    // Current channel

// Global Variables
CH N;            // Target channel
short M;         // # of broken buttons
bool broken[10]; // Whether the button is broken or not

// Function Prototypes
void get_input();
void run();
void set_output();
void deallocate();
int main();

int get_digits(CH ch);
CH get_opt_ch_upper(const CH &target_ch);
CH get_opt_ch_lower(const CH &target_ch);

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

    int digits = get_digits(N);

    memset(broken, false, sizeof(bool) * 10);
    int broken_ch;
    for (int i = 0; i < M; i++)
    {
        cin >> broken_ch;
        broken[broken_ch] = true;
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
    cout << "N (Target channel) : " << N << '\n';
    cout << "M : " << M << '\n';
    cout << "Lower CH : " << get_opt_ch_lower(N) << '\n';
    cout << "Upper CH : " << get_opt_ch_upper(N) << "\n\n";
#endif

#ifndef DEBUG_MODE
    if (M < 10)
    {
        CH opt_ch_upper = get_opt_ch_upper(N);
        CH opt_ch_lower = get_opt_ch_lower(N);

        int upper_cnt = abs(opt_ch_upper - N) + get_digits(opt_ch_upper); // Move to upper optimized channel of target channel (then, press the - button appropriate) 
        int lower_cnt = abs(opt_ch_lower - N) + get_digits(opt_ch_lower); // Move to lower optimized channel of target channel (then, press the + button appropriate)
        int brute_forcing_cnt = abs(N - CURR_CH);                         // Pressing only the +/- button to move the target channel

        cout << min({upper_cnt, lower_cnt, brute_forcing_cnt}) << '\n';   // Which is the best of 3 cases?
    }
    else // All digit button are broken
        cout << abs(N - CURR_CH) << '\n';
#endif
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
 *  Function Name : get_digits
 *  Parameters    : 1) ch (int) : Channel number
 *  Return Type   : int
 *  Description   : It returns the number of digits of the channel input
 */
int get_digits(CH ch)
{
    if (ch < 0)
        throw "Wrong input: Channel can not be negative";

    if (ch == 0 || ch == 1)
        return 1;

    return log10(ch) + 1;
}

/*
 *  Function Name : get_opt_ch_upper
 *  Parameters    : 1) ch (int) : Channel number
 *  Return Type   : int
 *  Description   : It returns the lowest channel among channels above the target channel that can be moved directly by pressing the button
 */
CH get_opt_ch_upper(const CH &target_ch)
{
    CH opt_ch = target_ch;

    while (abs(opt_ch - target_ch) < abs(target_ch - CURR_CH))
    {
        int digits = get_digits(opt_ch);
        int num = opt_ch;
        int i;

        for (i = 0; i < digits; i++)
        {
            if (broken[num % 10])
            {
                opt_ch++;
                break;
            }
            else
            {
                num /= 10;
            }
        }

        if (i == digits)
            return opt_ch;
    }

    return MAX_CH;
}

/*
 *  Function Name : get_opt_ch_lower
 *  Parameters    : 1) ch (int) : Channel number
 *  Return Type   : int
 *  Description   : It returns the highest channel among channels below the target channel that can be moved directly by pressing the button
 */
CH get_opt_ch_lower(const CH &target_ch)
{
    CH opt_ch = target_ch;

    while (opt_ch >= 0)
    {
        int digits = get_digits(opt_ch);
        int num = opt_ch;
        int i;

        for (i = 0; i < digits; i++)
        {
            if (broken[num % 10])
            {
                opt_ch--;
                break;
            }
            else
            {
                num /= 10;
            }
        }

        if (i == digits)
            return opt_ch;
    }
    
    return MAX_CH;
}
