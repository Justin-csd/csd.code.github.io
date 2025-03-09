#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
#define MAX 100100
inline int read()
{
    int x = 0;
    bool t = false;
    char ch = getchar();
    while ((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();
    if (ch == '-')
        t = true, ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = x * 10 + ch - 48, ch = getchar();
    return t ? -x : x;
}
int n;
int h[MAX];
int dA[MAX], dB[MAX];
namespace Destination
{
    int nt[MAX], lt[MAX], p[MAX], id[MAX];
    bool cmp(int a, int b) { return h[a] < h[b]; }
    void upd(int &mx, int &mxx, int i, int j)
    {
        int s = abs(h[i] - h[j]);
        if (!j)
            return;
        if (!mx || s < abs(h[i] - h[mx]) || (s == abs(h[i] - h[mx]) && h[j] < h[mx]))
            swap(mx, mxx), mx = j;
        else if (!mxx || s < abs(h[i] - h[mxx]) || (s == abs(h[i] - h[mxx]) && h[j] < h[mxx]))
            mxx = j;
    }
    void Work()
    {
        for (int i = 1; i <= n; ++i)
            p[i] = i;
        sort(&p[1], &p[n + 1], cmp);
        for (int i = 1; i <= n; ++i)
            lt[p[i]] = p[i - 1], nt[p[i]] = p[i + 1];
        for (int i = 1; i <= n; ++i)
        {
            int mx = 0, mxx = 0;
            upd(mx, mxx, i, lt[i]);
            upd(mx, mxx, i, lt[lt[i]]);
            upd(mx, mxx, i, nt[i]);
            upd(mx, mxx, i, nt[nt[i]]);
            nt[lt[i]] = nt[i];
            lt[nt[i]] = lt[i];
            lt[0] = nt[0] = 0;
            dA[i] = mxx;
            dB[i] = mx;
        }
    }
}
int p[17][MAX], sA[17][MAX], sB[17][MAX];
void Query(int S, int X, int &disA, int &disB)
{
    disA = disB = 0;
    for (int i = 16; ~i; --i)
        if (p[i][S] && X >= sA[i][S] + sB[i][S])
            disA += sA[i][S], disB += sB[i][S], X -= sA[i][S] + sB[i][S], S = p[i][S];
    if (dA[S] && X >= abs(h[S] - h[dA[S]]))
        disA += abs(h[S] - h[dA[S]]);
}
int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
        h[i] = read();
    Destination::Work();
    for (int i = 1; i <= n; ++i)
    {
        p[0][i] = dB[dA[i]];
        sA[0][i] = abs(h[i] - h[dA[i]]);
        sB[0][i] = abs(h[dA[i]] - h[dB[dA[i]]]);
    }
    for (int i = 1; i < 17; ++i)
        for (int j = 1; j <= n; ++j)
        {
            p[i][j] = p[i - 1][p[i - 1][j]];
            sA[i][j] = sA[i - 1][j] + sA[i - 1][p[i - 1][j]];
            sB[i][j] = sB[i - 1][j] + sB[i - 1][p[i - 1][j]];
        }
    int X = read();
    double Rate = 1e18;
    int pos = 0;
    for (int i = 1; i <= n; ++i)
    {
        int disA, disB;
        double V = 0;
        Query(i, X, disA, disB);
        if (!disB)
            V = 1e18 - 1;
        else
            V = 1.0 * disA / disB;
        if (V < Rate)
            Rate = V, pos = i;
        else if (V == Rate && h[i] > h[pos])
            pos = i;
    }
    printf("%d\n", pos);
    int Q = read();
    while (Q--)
    {
        int S = read(), X = read(), disA, disB;
        Query(S, X, disA, disB);
        printf("%d %d\n", disA, disB);
    }
    return 0;
}