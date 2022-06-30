/*
 * [Author]
 * Byeong Heon Lee
 * lww7438@gmail.com
 * https://dad-rock.tistory.com/922 (Korean)
 *
 */

// Problem URL
// https://www.acmicpc.net/problem/5430

// Debug Switch
// #define DEBUG_MODE

// Header Files
#include <iostream>
#include <cstring>

// Namespace & Aliases
using namespace std;
typedef unsigned int INDEX;
typedef short ELEMENT;

// Constants
const INDEX SIZE = 100000;     // Maximum size of input string
const char *DELIMITER = "[,]"; // Delimiters '[', ',', ']'


// Global Variables
char p[SIZE + 1];                        // input functions
INDEX n;                                 // # of functions
char str_array[SIZE * 3 + SIZE - 1 + 2]; // String to store the input array
ELEMENT int_array[SIZE];                 // Array to store elements of the array str_array
INDEX front;                             // Front index of int_array
INDEX back;                              // Back index of int_array
bool ERROR = false;                      // Error flag

// Function Prototypes
void get_input();
void run();
void set_output();
void deallocate();
int main();

void reverse();
bool drop();
void swap(INDEX *a, INDEX *b);

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

    cin >> p;
    cin >> n;
    cin >> str_array;

    front = 0;
    back = n - 1;

    if (n == 0)
    {
        back = 0;
        return;
    }

    int idx = 0;
    char *token;
    token = strtok(str_array, DELIMITER);
    while (token != NULL)
    {
        int_array[idx++] = atoi(token);
        token = strtok(NULL, DELIMITER);
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
    int p_size = strlen(p);

    for (int i = 0; i < p_size; i++)
    {
        if (p[i] == 'R')
            reverse();
        else if (p[i] == 'D')
        {
            if (!drop())
            {
                ERROR = true; // Set the error flag (Soft error)
                return;
            }
        }
        else
            throw "Error: Unexpected input"; // Hard Error
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
    if (ERROR)
    {
        cout << "error\n";
        return;
    }

    if (n == 0)
    {
        cout << "[]\n";
        return;
    }

    cout << '[';
    if (front <= back)
    {
        for (int i = front; i < back; i++)
            cout << int_array[i] << ',';
        cout << int_array[back];
    }
    else
    {
        for (int i = front; i > back; i--)
            cout << int_array[i] << ',';
        cout << int_array[back];
    }
    cout << "]\n";
}

/*
 *  Function Name : deallocate
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Deallocate the heap and initialize the global variables and flags
 */
void deallocate()
{
    memset(str_array, '\0', sizeof(char) * (SIZE * 3 + SIZE - 1 + 2));
    memset(int_array, 0, sizeof(ELEMENT) * SIZE);
    ERROR = false;
}

/*
 *  Function Name : main
 *  Parameters    : -
 *  Return Type   : -
 *  Description   : Main Function
 */
int main()
{
    int T; // # of test cases
    cin >> T;

    while (T--)
    {
        get_input();
        run();
        set_output();
        deallocate();
    }

    return EXIT_SUCCESS;
}

void reverse()
{
    swap(&front, &back);
}

bool drop()
{
    if (n == 0)
        return false;

    if (front <= back)
        front++;
    else
        front--;

    n--;
    return true;
}

void swap(INDEX *a, INDEX *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
