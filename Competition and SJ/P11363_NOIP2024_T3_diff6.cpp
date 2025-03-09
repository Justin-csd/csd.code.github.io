#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

#define pb push_back

using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

template <typename T>
inline void read(T &x)
{
    x = 0;
    bool F = 0;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            F = 1;
    for (; isdigit(c); c = getchar())
        x = x * 10 + (c ^ 48);
    if (F)
        x = -x;
}

template <typename T1, typename... T2>
inline void read(T1 &x, T2 &...y)
{
    read(x);
    read(y...);
}

template <typename T>
inline void checkmax(T &a, const T &b)
{
    if (a < b)
        a = b;
}

template <typename T>
inline void checkmin(T &a, const T &b)
{
    if (a > b)
        a = b;
}

const int N = 1e5 + 5;
const ll MOD = 1e9 + 7;
int n, m, u[N], v[N], flag_edge[N], d[N];
vector<PII> adj[N];
ll sum[N][2], inv[N], ans;

void dfs(int u, int parent)
{
    sum[u][0] = sum[u][1] = 0;
    ll val = 0;
    for (auto &x : adj[u])
    {
        int v = x.first;
        if (v == parent)
            continue;
        dfs(v, u);
        if (x.second)
            sum[v][1] += sum[v][0], sum[v][0] = 0;
        val = (val + sum[v][1] * (sum[u][0] + sum[u][1]) + sum[v][0] * sum[u][1]) % MOD;
        sum[u][0] = (sum[u][0] + sum[v][0]) % MOD;
        sum[u][1] = (sum[u][1] + sum[v][1]) % MOD;
    }
    ll INV = inv[d[u]];
    ans = (ans + val * INV) % MOD;
    if (!d[u])
        sum[u][0]++;
    sum[u][0] = (sum[u][0] * INV) % MOD;
    sum[u][1] = (sum[u][1] * INV) % MOD;
}

inline void solve()
{
    read(n, m);
    for (int i = 1; i <= n; i++)
    {
        d[i] = -1;
        adj[i].clear();
    }
    ans = 0;
    for (int i = 1; i < n; i++)
    {
        read(u[i], v[i]);
        flag_edge[i] = 0;
        d[u[i]]++;
        d[v[i]]++;
    }
    int t;
    while (m--)
    {
        read(t);
        flag_edge[t] = 1;
    }
    if (n == 2)
    {
        printf("1\n");
        return;
    }
    for (int i = 1; i < n; i++)
    {
        adj[u[i]].pb( {v[i], flag_edge[i]} );
        adj[v[i]].pb( {u[i], flag_edge[i]} );
    }
    int root = 0;
    for (int i = 1; i <= n; i++)
    {
        if (d[i])
        {
            root = i;
            break;
        }
    }
    dfs(root, 0);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= d[i]; j++)
        {
            ans = (ans * j) % MOD;
        }
    }
    printf("%lld\n", ans);
}

int main()
{
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; i++)
    {
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    }
    int c, t;
    read(c, t);
    while (t--)
        solve();
    return 0;
}