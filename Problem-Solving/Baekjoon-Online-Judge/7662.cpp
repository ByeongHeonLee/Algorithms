/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/927 (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/7662

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <set>

// Namespace & Aliases
using namespace std;
typedef int INT;

// Constants
const int MAX = 1000;

// Global Variables
multiset<int> heap; // Priority queue (Heap)
int T;              // # of test cases
int k;              // # of operations for priority queue
char op_code;       // Operation code
int n;              // Item for operation

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

    cin >> op_code >> n;
}

/*
 *  Function Name : run
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Main Logic
 */
void run()
{
    if (op_code == 'I')
        heap.insert(n);
    else if (op_code == 'D')
    {
        if (heap.empty())
            return;
            
        if (n == -1)
            heap.erase(heap.begin());
        else if (n == 1)
            heap.erase(--heap.end());
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
    if (heap.empty())
        cout << "EMPTY\n";
    else
        cout << *(--heap.end()) << ' ' << *(heap.begin()) << '\n';
}

/*
 *  Function Name : deallocate
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Deallocate the heap
 */
void deallocate()
{
    heap.clear();
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
        cin >> k;
        while (k--)
        {
            get_input();
            run();
        }

        set_output();
        deallocate();
    }

    return EXIT_SUCCESS;
}
