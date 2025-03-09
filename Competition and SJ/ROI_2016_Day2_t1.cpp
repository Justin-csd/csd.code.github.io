#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
#define rep(i, a, b) for (int i = a, i##end = b; i <= i##end; ++i)
#define drep(i, a, b) for (int i = a, i##end = b; i >= i##end; --i)
template <class T>
inline void cmin(T &a, T b) { ((a > b) && (a = b)); }

const int N = 3e5 + 10, INF = 1e9 + 10, D = 6;
//二指禅
int n, m;
char T[N];
int Pow1[N], Pow2[N];
int S[N];
const ll K1 = 19260817, P1 = 114514;
const ll K2 = 1e9 + 13, P2 = 1919810;

struct Solver
{
    int S[N];
    int trie[N][2], s[N], cnt, H1[N], H2[N];
    int fa[N], top[N], sz[N], h1[N], h2[N], son[N], lst[N], bot[N], L[N], id[N], dfn, dep[N];
    // lst[i] 记录祖先中第一个s[f]!=s[i]的节点
    void dfs(int u)
    {
        sz[u] = 1;
        if (s[u] == s[fa[u]])
            lst[u] = lst[fa[u]];
        else
            lst[u] = fa[u];
        rep(i, 0, 1)
        {
            int v = trie[u][i];
            if (!v)
                continue;
            fa[v] = u, dep[v] = dep[u] + 1;
            h1[v] = (h1[u] * K1 + i + 1) % P1;
            h2[v] = (h2[u] * K2 + i + 1) % P2;
            dfs(v);
            sz[u] += sz[v];
            if (son[u] == 0 || sz[v] > sz[son[u]])
                son[u] = v;
        }
    }
    void dfs(int u, int t)
    {
        id[L[u] = ++dfn] = u;
        bot[top[u] = t] = u;
        if (son[u])
            dfs(son[u], t);
        for (int v : trie[u])
            if (v && v != son[u])
                dfs(v, v);
    }
    void Ins(char *T, int l, int w)
    {
        int now = 0;
        rep(i, 1, l)
        {
            int c = T[i] - '0';
            if (!trie[now][c])
                s[trie[now][c] = ++cnt] = 2e9;
            cmin(s[now = trie[now][c]], w);
        }
    }
    void Init()
    {
        rep(i, 1, n)
        {
            H1[i] = (H1[i - 1] * K1 + S[i] + 1) % P1;
            H2[i] = (H2[i - 1] * K2 + S[i] + 1) % P2;
        }
        dfs(0), dfs(0, 0);
    }
    int Que(int i)
    {
        // 求i 的最长匹配位置
        int u = 0;
        while (i <= n)
        {
            if (!trie[u][S[i]])
                break;
            if (trie[u][S[i]] != son[u])
            {
                u = trie[u][S[i++]];
                continue;
            }
            int l = 1, r = min(n - i + 1, dep[bot[top[u]]] - dep[u]), res = 1;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if ((H1[i + mid - 1] - 1ll * H1[i - 1] * Pow1[mid] % P1 + P1) % P1 == (h1[id[L[u] + mid]] - 1ll * h1[u] * Pow1[mid] % P1 + P1) % P1 &&
                    (H2[i + mid - 1] - 1ll * H2[i - 1] * Pow2[mid] % P2 + P2) % P2 == (h2[id[L[u] + mid]] - 1ll * h2[u] * Pow2[mid] % P2 + P2) % P2)
                    l = mid + 1, res = mid;
                else
                    r = mid - 1;
            }
            i += res, u = id[L[u] + res];
        }
        return u;
    }
} X, Y;

struct BIT
{
    ll s[N];
    void Init()
    {
        memset(s, 127, sizeof s);
    }
    void Add(int p, ll x)
    {
        while (p)
            cmin(s[p], x), p -= p & -p;
    }
    ll Que(int p)
    {
        ll res = 1e18;
        while (p <= n)
            cmin(res, s[p]), p += p & -p;
        return res;
    }
} TX, TY;
ll dp[N];

int main()
{
    rep(i, Pow1[0] = Pow2[0] = 1, N - 1)
    {
        Pow1[i] = Pow1[i - 1] * K1 % P1;
        Pow2[i] = Pow2[i - 1] * K2 % P2;
    }
    scanf("%d%d%*d", &n, &m);
    rep(i, 1, n) scanf("%1d", S + i), X.S[i] = Y.S[n - i + 1] = S[i];
    rep(t, 1, m)
    {
        int w, l;
        scanf("%d%s", &w, T + 1), l = strlen(T + 1);
        X.Ins(T, l, w), reverse(T + 1, T + l + 1), Y.Ins(T, l, w);
    }
    X.Init(), Y.Init();

    rep(i, 1, n) dp[i] = 1e18;
    TX.Init(), TY.Init();
    TY.Add(1, 0);
    rep(i, 0, n)
    {
        // 暴力维护转移
        if (i)
        {
            cmin(dp[i], TX.Que(i));
            int u = Y.Que(n - i + 1);
            while (u)
            {
                int l = Y.dep[Y.lst[u]] + 1, r = Y.dep[u];
                if (r - l + 1 <= D)
                    rep(j, l, r) cmin(dp[i], dp[i - j] + Y.s[u]);
                else
                    cmin(dp[i], TY.Que(i - r + 1) + Y.s[u]);
                u = Y.lst[u];
            }
        }
        TY.Add(i + 1, dp[i]);
        if (i == n || dp[i] == 1e18)
            continue;
        int u = X.Que(i + 1);
        while (u)
        {
            int l = X.dep[X.lst[u]] + 1, r = X.dep[u];
            if (r - l + 1 <= D)
                rep(j, l, r) cmin(dp[i + j], dp[i] + X.s[u]);
            else
                TX.Add(i + r, dp[i] + X.s[u]);
            u = X.lst[u];
        }
    }
    printf("%lld\n", dp[n] < 1e18 ? dp[n] : -1);
}