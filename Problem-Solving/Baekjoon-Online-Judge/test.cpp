#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <cmath>
#include <string.h>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    // 1 ≤ N ≤ 500,000, 단, N 은 홀수
    int N;
    std::cin >> N;

    // N 개의 숫자 입력
    int v[500001] = {0};
    int count[8001];
    memset(count, 0, sizeof(int) * 8001);
    int max = 0;
    int sum=0;

    // |n| <= 4,000
    for (int i = 0; i < N; ++i)
    {
        std::cin >> v[i];
        sum += v[i];
        int tmp = (v[i] <= 0) ? abs(v[i]) : v[i] + 4000;
        ++count[tmp];
        if (count[tmp] > max)
            max = count[tmp];
    }

    // 결과 출력

    // 계산의 편의를 위해 미리 정렬을 합니다
    std::sort(v, v + N);

    // 평균(average)
    int avg = round((double)sum/(double)N);
    if(avg)
        std::cout << avg << '\n';
    else
        std::cout << "0\n";

    // 중앙값(median)
    std::cout << v[N / 2] << '\n';

    // 최빈값(mode)
    int mode = 0;
    bool is_second = false;
    for (int i = -4000; i < 4001; ++i)
    {
        int tmp = (i <= 0) ? abs(i) : i + 4000;
        if (count[tmp] == max)
        {
            mode = i;
            if (is_second)
                break;
            is_second = true;
        }
    }
    std::cout << mode << '\n';

    // 범위(range)
    std::cout << v[N - 1] - v[0] << '\n';

    return 0;
}