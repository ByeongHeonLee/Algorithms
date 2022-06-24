#include "smatching.h"

vector<int> find_bf(const string &str, const string &pat)
{
    const int strSize = str.size();
    const int patSize = pat.size();

    if (strSize < patSize)
        throw "Main String must be greater than substring";

    vector<int> result(strSize - patSize + 1, -1);

    for (int i = 0; i < strSize - patSize + 1; i++)
    {
        int j=0;
        while (j < patSize)
        {
            if(str[i+j] == pat[j])
                j++;
            else
                break;
        }
        if(j == patSize)
            result.push_back(i);
    }

    return result;
}

vector<int> find_rk(const string &str, const string &pat)
{
    // String Matching using Rabin-Karp Algorithm

    ull hstr = 0, hpat = 0;
    const int strSize = str.size();
    const int patSize = pat.size();

    if (strSize < patSize)
        throw "Main String must be greater than substring";

    vector<int> result(strSize - patSize + 1, -1);

    // compute the hash value of "str" and "pat"
    int coef;
    for (int i = 0; i < patSize; i++)
    {
        coef = ull(pow(RADIX, i));
        hstr += long(coef * str[patSize - 1 - i]);
        hpat += long(coef * pat[patSize - 1 - i]);
    }

    coef = ull(pow(RADIX, patSize - 1));
    for (int i = 0; i < strSize - patSize + 1; i++)
    {
        if (hstr == hpat)
            check(str.substr(i, patSize), pat, i, result);
        hstr = ((RADIX * (hstr - coef * str[i])) + str[patSize + i]);
    }

    return result;
}

bool check(string str, string pat, int index, vector<int> &result)
{
    const int patSize = pat.size();

    int i;
    for (i = 0; i < patSize; i++)
        if (str[i] != pat[i])
            break;

    if (i == patSize)
    {
        result.push_back(index);
        return true;
    }
    return false;
}

vector<int> find_bm(const string &str, const string &pat)
{
    // String Matching using Boyer-Moore Algorithm

    const int strSize = str.size();
    const int patSize = pat.size();

    if (strSize < patSize)
        throw "Main String must be greater than substring";

    vector<int> result(strSize - patSize + 1, -1);

    int strIndex, patIndex;
    for (int i = 0; i < strSize - patSize + 1;)
    {
        strIndex = i + patSize - 1;
        patIndex = patSize - 1;
        while (patIndex >= 0 && str[strIndex] == pat[patIndex])
        {
            strIndex--;
            patIndex--;
        }
        if (patIndex == -1)
            result.push_back(i);

        i += compute_jump(pat, str[i + patSize - 1]);
    }

    return result;
}

int compute_jump(const string &pat, const char &str)
{
    int patSize = pat.size();
    int jump;

    if (pat[patSize - 1] == str)
        return patSize;

    for (int i = patSize - 2; i >= 0; i--)
        if (pat[i] == str)
            return patSize - 1 - i;

    return patSize;
}

vector<int> find_kmp(const string &str, const string &pat)
{
    // String Matching using KMP(Knuth-Morris-Pratt) Algorithm

    const int strSize = str.length();
    const int patSize = pat.length();

    if (strSize < patSize)
        throw "Main String must be greater than substring";

    // 실패 함수값을 구해놓았다는 가정.
    vector<int> f = failure_func(pat);
    vector<int> result(strSize - patSize + 1, -1);

    int begin = 0; // Starting index
    int m = 0;     // # of matched character
    while (begin <= strSize - patSize)
    {
        // 일치개수(m)가 S의 길이보다 작고
        // H[begin+m]과의 문자가 일치하는 경우
        if (m < patSize && str[begin + m] == pat[m])
        {
            m++;
            // S를 찾은 경우에 begin값을 저장한다.
            if (m == patSize)
                result.push_back(begin);
        }
        // 불일치하거나 S를 찾은 경우
        else
        {
            // 일치한적이 한번도 없고 불일치했다면 단순히 begin 옮기면 된다.
            if (m == 0)
                begin++;
            // 그게 아니라면 begin과 m을 위에서 말한 것처럼 초기화!
            else
            {
                begin += (m - f[m - 1]);
                m = f[m - 1];
            }
        }
    }
    return result;
}

vector<int> failure_func(const string &pat)
{
    int patSize = pat.length();
    vector<int> f(patSize, 0);
    int begin = 1, m = 0;

    while (begin + m < patSize)
    {
        // 일치하면 m을 증가시키고 실패함수를 초기화한다.
        if (pat[begin + m] == pat[m])
        {
            m++;
            f[begin + m - 1] = m;
        }
        else
        {
            if (m == 0)
                begin++;
            else
            {
                begin += (m - f[m - 1]);
                m = f[m - 1];
            }
        }
    }
    return f;
}