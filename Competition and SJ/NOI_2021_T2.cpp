#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 210, mod = 998244353;
int T, n, k, a[N], sz[N];
int c[N][N], d[N][N];
inline int add(int x, int y) { return (x + y >= mod) ? x + y - mod : x + y; }
inline int dec(int x, int y) { return (x - y < 0) ? x - y + mod : x - y; }
inline int ksm(int x, int y)
{
    int ret = 1;
    for (; y; y >>= 1, x = 1ll * x * x % mod)
        if (y & 1)
            ret = 1ll * ret * x % mod;
    return ret;
}
inline int del(int n)
{
    int ans = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (!c[i][i])
        {
            for (int j = i + 1; j <= n; ++j)
                if (c[j][i])
                {
                    swap(c[i], c[j]);
                    ans = dec(0, ans);
                    break;
                }
        }
        if (!c[i][i])
            return 0;
        ans = 1ll * ans * c[i][i] % mod;
        int iv = ksm(c[i][i], mod - 2);
        for (int j = i; j <= n; ++j)
            c[i][j] = 1ll * c[i][j] * iv % mod;
        for (int j = i + 1; j <= n; ++j)
            for (int k = n; k >= i; --k)
                c[j][k] = dec(c[j][k], 1ll * c[i][k] * c[j][i] % mod);
    }
    return ans;
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &k);
        for (int i = 1; i <= k; ++i)
            scanf("%d", &a[i]);
        for (int i = 1; i < k; ++i)
            scanf("%d", &sz[i]);
        for (int i = 1; i <= a[1]; ++i)
            for (int j = 1; j <= a[1]; ++j)
                c[i][j] = i == j ? 1 : 0;
        for (int i = 1; i < k; ++i)
        {
            for (int j = 1, u, v; j <= sz[i]; ++j)
            {
                scanf("%d%d", &u, &v);
                for (int k = 1; k <= a[1]; ++k)
                    d[k][v] = add(d[k][v], c[k][u]);
            }
            for (int j = 1; j <= a[1]; ++j)
                for (int k = 1; k <= a[i + 1]; ++k)
                    c[j][k] = d[j][k], d[j][k] = 0;
        }
        printf("%d\n", del(a[1]));
    }
    return 0;
}