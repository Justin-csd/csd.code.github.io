#include <cstdio>
#include <cctype>
#define print(x, y) write(x), putchar(y)

template <class T>
inline T read(const T sample)
{
    T x = 0;
    char s;
    bool f = 0;
    while (!isdigit(s = getchar()))
        f |= (s == '-');
    for (; isdigit(s); s = getchar())
        x = (x << 1) + (x << 3) + (s ^ 48);
    return f ? -x : x;
}
template <class T>
inline void write(T x)
{
    static int writ[50], w_tp = 0;
    if (x < 0)
        putchar('-'), x = -x;
    do
        writ[++w_tp] = x - x / 10 * 10, x /= 10;
    while (x);
    while (putchar(writ[w_tp--] ^ 48), w_tp)
        ;
}

#include <cstring>
#include <iostream>
using namespace std;

const int maxn = 1200005;
const int mod = 998244353;

int inv(int x, int y = mod - 2, int r = 1)
{
    for (; y; y >>= 1, x = 1ll * x * x % mod)
        if (y & 1)
            r = 1ll * r * x % mod;
    return r;
}
int dec(int x, int y) { return x - y < 0 ? x - y + mod : x - y; }
int inc(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }

bool vis[maxn];
int n, fac[maxn], ifac[maxn];

void initialize()
{
    fac[0] = 1;
    for (int i = 1; i <= maxn - 5; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[maxn - 5] = inv(fac[maxn - 5]);
    for (int i = maxn - 6; i >= 0; --i)
        ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
}

int C(int n, int m)
{
    if (m < 0 || n < m)
        return 0;
    return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int f(int i, int j) { return dec(
    C(n * 2 - i - j - 1, n - i - 1), C(n * 2 - i - j - 1, n - i + 1)); }

void CandyMyWife()
{
    bool judge = false;
    n = read(9);
    int lim = 0, ans = 0, val = 1;
    memset(vis, 0, sizeof(bool) * (n + 2));
    for (int i = 1; i <= n; ++i)
    {
        int x = read(9);
        if (judge)
            continue;
        ans = inc(ans, f(i - 1, max(lim, x) + 1));
        if (val < x && x < lim)
            judge = true;
        lim = max(lim, x);
        vis[x] = true;
        while (vis[val])
            ++val;
    }
    print(ans, '\n');
}

int main()
{
    initialize();
    for (int T = read(9); T; --T)
        CandyMyWife();
    return 0;
}