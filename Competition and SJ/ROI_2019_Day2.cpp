#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
signed main()
{
    // free();
    int a, b, c;
    cin >> a >> b >> c;
    if (c == 2)
    {
        cout << abs(a - b) / 2;
    }
    int tmp = a;
    int cnt = 0;
    if (c == 2)
    {
        printf("%d", (b - a) / 2);
        exit(0);
    }
    while (tmp != b)
    {
        int x = c - tmp % c; // 距离c的倍数差几
        if (x & 1)
        { // x是奇数时一直+2，肯定不会是c的倍数
            if (tmp + x + 1 <= b)
            {
                tmp += x + 1;
                cnt += x / 2 + 1;
            }
            else
            {
                cnt += ceil((b - tmp) / 2.0);
                break;
            }
        }
        else
        { // 否则要考虑+1的情况
            if (tmp + x + 1 <= b)
            {
                tmp += x + 1;
                cnt += x / 2 + 1;
            }
            else
            {
                cnt += ceil((b - tmp) / 2.0);
                break;
            }
        }
    }
    cout << cnt;
    return 0;
}