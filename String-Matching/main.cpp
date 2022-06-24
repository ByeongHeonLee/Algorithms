#include "smatching.h"

void showVector(vector<int>& result);

int main()
{
    string str = "i gonna sleep, i want to sleep, i hope to sleep, deep sleep";
    string pat = "sleep";

    vector<int> result;

    result = find_bf(str, pat);
    showVector(result);
    result.clear();

    result = find_rk(str, pat);
    showVector(result);
    result.clear();

    result = find_bm(str, pat);
    showVector(result);
    result.clear();

    result = find_kmp(str, pat);
    showVector(result);
    result.clear();

    return 0;
}

void showVector(vector<int>& result)
{
    for (vector<int>::iterator it = result.begin(); it != result.end(); ++it)
    {
        if (*it == -1)
            continue;
        cout << *it << ' ';
    }
    printf("\n");
}