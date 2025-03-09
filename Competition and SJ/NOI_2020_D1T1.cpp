#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
using ll = long long;
int c[55];
int id[515][8], tot;
struct matrix
{
    ll mat[255][255];
    matrix() { memset(mat, 0xcf, sizeof mat); }
    ll *operator[](int x) { return mat[x]; }
    matrix operator*(matrix &b)
    {
        matrix c;
        for (int i = 1; i <= tot; ++i)
            for (int j = 1; j <= tot; ++j)
                for (int k = 1; k <= tot; ++k)
                    c[i][j] = max(c[i][j], mat[i][k] + b[k][j]);
        return c;
    }
} g[32];
struct event
{
    int t, x, y;
    bool operator<(const event &sec) const { return t < sec.t; }
} a[255];
ll ans[255];
ll tmp[255];
void mul(int p)
{
    for (int i = 1; i <= tot; ++i)
        tmp[i] = -1e18;
    for (int i = 1; i <= tot; ++i)
        for (int j = 1; j <= tot; ++j)
            tmp[j] = max(tmp[j], 1ll * (ans[i] + g[p][i][j]));
    for (int i = 1; i <= tot; ++i)
        ans[i] = tmp[i];
}
int main()
{
    int n, m, T, K;
    cin >> n >> m >> T >> K;
    for (int i = 1; i <= n; ++i)
        cin >> c[i];
    for (int i = 1; i <= n; ++i)
        id[i][0] = ++tot;
    for (int i = 1; i <= m; ++i)
    {
        int x, y, z;
        cin >> x >> y >> z;
        for (int j = 1; j < z; ++j)
            if (!id[x][j])
                id[x][j] = ++tot;
        for (int j = 1; j < z; ++j)
            g[0][id[x][j - 1]][id[x][j]] = 0;
        g[0][id[x][z - 1]][y] = c[y];
    }
    for (int i = 1; i <= K; ++i)
        cin >> a[i].t >> a[i].x >> a[i].y;
    sort(a + 1, a + K + 1);
    for (int i = 1; i <= 30; ++i)
        g[i] = g[i - 1] * g[i - 1];
    ans[1] = c[1];
    for (int i = 2; i <= tot; ++i)
        ans[i] = -1e18;
    a[K + 1].t = T;
    for (int i = 1; i <= K + 1; ++i)
    {
        int d = a[i].t - a[i - 1].t;
        for (int j = 30; ~j; --j)
            if ((d >> j) & 1)
                mul(j);
        ans[a[i].x] += a[i].y;
    }
    if (ans[1] >= 0)
        cout << ans[1] << '\n';
    else
        cout << -1 << '\n';
    return 0;
}