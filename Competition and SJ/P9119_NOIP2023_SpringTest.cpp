#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;
using Ldouble = long double;

constexpr int _N = 1e3 + 5;
int n, K;

struct Node
{
    Ldouble x, y;
} po[_N];

struct TriPair
{
    int fir, sec, thi;

    TriPair() {}
    TriPair(int fir, int sec, int thi) : fir(fir), sec(sec), thi(thi) {}
};

Ldouble f[_N][_N][2];
TriPair from[_N][_N][2];

inline Ldouble Sqr(Ldouble x)
{
    return x * x;
}

inline Ldouble Dist(int i, int j)
{
    return sqrt(Sqr(po[i].x - po[j].x) + Sqr(po[i].y - po[j].y));
}

inline int Lp(int x)
{
    return K - x <= 0 ? K - x + n : K - x;
}

inline int Rp(int x)
{
    return K + x > n ? K + x - n : K + x;
}

void Output(TriPair cur)
{
    if (cur.fir == 0 && cur.sec == 0)
        return cout << K << ' ', void();

    Output(from[cur.fir][cur.sec][cur.thi]);

    if (cur.thi)
        cout << Rp(cur.sec) << ' ';
    else
        cout << Lp(cur.fir) << ' ';
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> po[i].x >> po[i].y;

    double tmpMax = -1e8;

    for (int i = 1; i <= n; ++i)
        if (po[i].y > tmpMax)
            tmpMax = po[i].y, K = i;

    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            f[i][j][0] = f[i][j][1] = 1e18;

    f[0][0][0] = f[0][0][1] = 0;
    Ldouble val;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0, jend = n - j; j < jend; ++j)
        {
            if (i)
            {
                val = f[i - 1][j][0] + Dist(Lp(i - 1), Lp(i));

                if (f[i][j][0] > val)
                    f[i][j][0] = val, from[i][j][0] = TriPair(i - 1, j, 0);

                val = f[i - 1][j][1] + Dist(Rp(j), Lp(i));

                if (f[i][j][0] > val)
                    f[i][j][0] = val, from[i][j][0] = TriPair(i - 1, j, 1);
            }

            if (j)
            {
                val = f[i][j - 1][0] + Dist(Lp(i), Rp(j));

                if (f[i][j][1] > val)
                    f[i][j][1] = val, from[i][j][1] = TriPair(i, j - 1, 0);

                val = f[i][j - 1][1] + Dist(Rp(j - 1), Rp(j));

                if (f[i][j][1] > val)
                    f[i][j][1] = val, from[i][j][1] = TriPair(i, j - 1, 1);
            }
        }
    }

    Ldouble ans = 1e18;
    TriPair pos;

    for (int i = 0; i < n; ++i)
    {
        if (ans > f[i][n - i - 1][0])
            ans = f[i][n - i - 1][0], pos = TriPair(i, n - i - 1, 0);

        if (ans > f[i][n - i - 1][1])
            ans = f[i][n - i - 1][1], pos = TriPair(i, n - i - 1, 1);
    }

    Output(pos);
}