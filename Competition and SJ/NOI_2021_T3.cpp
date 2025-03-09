#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int N = 3e5 + 20;
namespace iobuff
{
    const int LEN = 1000000;
    char in[LEN + 5], out[LEN + 5];
    char *pin = in, *pout = out, *ed = in, *eout = out + LEN;
    inline char gc(void)
    {
        return pin == ed && (ed = (pin = in) + fread(in, 1, LEN, stdin), ed == in) ? EOF : *pin++;
    }
    inline void pc(char c)
    {
        pout == eout && (fwrite(out, 1, LEN, stdout), pout = out);
        (*pout++) = c;
    }
    inline void flush() { fwrite(out, 1, pout - out, stdout), pout = out; }
    template <typename T>
    inline void read(T &x)
    {
        static int f;
        static char c;
        c = gc(), f = 1, x = 0;
        while (c < '0' || c > '9')
            f = (c == '-' ? -1 : 1), c = gc();
        while (c >= '0' && c <= '9')
            x = 10 * x + c - '0', c = gc();
        x *= f;
    }
    template <typename T>
    inline void putint(T x, char div)
    {
        static char s[15];
        static int top;
        top = 0;
        x < 0 ? pc('-'), x = -x : 0;
        while (x)
            s[top++] = x % 10, x /= 10;
        !top ? pc('0'), 0 : 0;
        while (top--)
            pc(s[top] + '0');
        pc(div);
    }
}
using namespace iobuff;
int n, m, q, k, first[N], cnt, dp[N], vis[N], l, r;
struct node
{
    int u, v, nxt, f;
} e[N << 2];
inline void add(int u, int v)
{
    e[++cnt].v = v;
    e[cnt].u = u;
    e[cnt].f = 1;
    e[cnt].nxt = first[u];
    first[u] = cnt;
}
int tot, dfn[N], ins[N], low[N], scc[N], stk[N], top, sum, siz[N], de[N];
vector<int> to[N], ru[N];
inline void tarjan(int u)
{
    dfn[u] = low[u] = ++tot;
    stk[++top] = u;
    ins[u] = 1;
    for (int i = first[u]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (!e[i].f)
            continue;
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (ins[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        int t;
        ++sum;
        siz[sum] = 0;
        do
        {
            t = stk[top--];
            ins[t] = 0;
            scc[t] = sum;
            siz[sum]++;
        } while (t != u);
    }
}
inline void work(int s, int t, int tp)
{
    memset(dfn + 1, 0, sizeof(int) * (n));
    tot = 0;
    top = 0;
    sum = 0;
    memset(low + 1, 0, sizeof(int) * (n));
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= sum; ++i)
        to[i].clear(), ru[i].clear();
    for (int i = 1; i <= m; ++i)
    {
        int u = e[i].u, v = e[i].v;
        if (scc[u] != scc[v])
            to[scc[u]].push_back(scc[v]), ru[scc[v]].push_back(scc[u]);
    }
    for (int i = cnt - k + 1; i <= cnt; ++i)
    {
        int u = e[i].u, v = e[i].v;
        if (scc[u] != scc[v])
            to[scc[u]].push_back(scc[v]), ru[scc[v]].push_back(scc[u]);
    }
}
inline void rebuild()
{
    for (int i = 1; i <= sum; ++i)
        to[i].clear();
    for (int u = 1; u <= sum; ++u)
    {
        int now = sum + 1;
        for (int i : ru[u])
            now = min(now, i);
        if (now != sum + 1)
            to[now].push_back(u);
    }
    for (int i = 1; i <= sum; ++i)
        ru[i].clear();
    for (int i = 1; i <= sum; ++i)
        for (int v : to[i])
            ru[v].push_back(i);
}
namespace sub
{
    int dftot, dep[N], in[N], out[N], st[N << 2][21], pa[N], tmp[N], euler[N << 2], lg[N << 2];
    inline void dfs(int u, int f, int x)
    {
        euler[++dftot] = u;
        in[u] = dftot;
        dep[u] = dep[f] + 1;
        tmp[u] = tmp[f] + siz[u];
        pa[u] = f;
        for (int v : to[u])
            dfs(v, u, x), euler[++dftot] = u;
        out[u] = dftot;
    }
    inline bool pd(int u, int v) { return in[u] <= in[v] && out[v] <= out[u]; }
    inline int calc(int s, int t)
    {
        if (pd(s, t))
            return tmp[t] - tmp[pa[s]];
        else
            return 0;
    }
    inline int gmin(int x, int y) { return dep[x] < dep[y] ? x : y; }
    inline void buildst()
    {
        lg[0] = -1;
        for (int i = 1; i <= dftot; ++i)
            lg[i] = lg[i >> 1] + 1;
        for (int i = 1; i <= dftot; ++i)
            st[i][0] = euler[i];
        for (int j = 1; (1 << j) <= dftot; ++j)
            for (int i = 1; i + (1 << j) - 1 <= dftot; ++i)
                st[i][j] = gmin(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
    }
    inline int LCA(int x, int y)
    {
        x = in[x];
        y = in[y];
        if (x > y)
            swap(x, y);
        int k = lg[y - x + 1];
        return gmin(st[x][k], st[y - (1 << k) + 1][k]);
    }
    int tt, stk[7], p[N], top, vis[N], vn[N], pn[N], val[N];
    int first[N], First[N], ct1[N], ct2[N];
    vector<int> ve;
    inline bool cmp(int x, int y) { return in[x] < in[y]; }
    node d[N], g[N];
    inline void link(int u, int v, int w)
    {
        if (!pn[u])
            pn[u] = 1, ve.push_back(u);
        if (!pn[v])
            pn[v] = 1, ve.push_back(v);
        ++cnt;
        val[cnt] = (u == v) ? w - siz[u] : w - siz[u] - siz[v];
        d[cnt].v = v;
        d[cnt].nxt = first[u];
        first[u] = cnt;
        g[cnt].v = u;
        g[cnt].nxt = First[v];
        First[v] = cnt;
    }
    inline void solve(int s, int tp)
    {
        if (vn[s])
            return;
        vn[s] = 1;
        for (int i = (!tp ? first[s] : First[s]); i; i = (!tp ? d[i].nxt : g[i].nxt))
        {
            int v = !tp ? d[i].v : g[i].v;
            vis[i] = 1;
            if (!vn[v])
                solve(v, tp);
        }
        return;
    }
    void main()
    {
        for (int i = 1; i <= sum; ++i)
            if (!ru[i].size())
                dfs(i, 0, i);
        buildst();
        for (tt = 1; tt <= q; ++tt)
        {
            int s, t;
            read(s);
            read(t);
            s = scc[s];
            t = scc[t];
            stk[0] = s;
            stk[1] = t;
            int num = 1;
            ve.clear();
            top = cnt = 0;
            for (int i = 1, u, v; i <= k; ++i)
            {
                read(u);
                read(v);
                stk[++num] = scc[u], stk[++num] = scc[v];
                link(scc[u], scc[v], siz[scc[u]] + siz[scc[v]]);
            }
            sort(stk, stk + num + 1, cmp);
            p[top = 1] = stk[0];
            for (int i = 1; i <= num; ++i)
            {
                int lca = LCA(p[top], stk[i]);
                while (top > 1 && dep[p[top - 1]] >= dep[lca])
                    link(p[top - 1], p[top], calc(p[top - 1], p[top])), top--;
                if (p[top] != lca)
                    link(lca, p[top], calc(lca, p[top])), p[top] = lca;
                p[++top] = stk[i];
            }
            while (top > 1)
                link(p[top - 1], p[top], calc(p[top - 1], p[top])), top--;
            solve(s, 0);
            for (int i = 1; i <= cnt; ++i)
                if (vis[i])
                    ct1[i] = 1, vis[i] = 0;
            for (int i : ve)
                if (vn[i])
                    ct2[i] = 1, vn[i] = 0;
            solve(t, 1);
            int ans = 0;
            for (int i = 1; i <= cnt; ++i)
            {
                if (vis[i] && ct1[i])
                    ans += val[i];
                ct1[i] = vis[i] = 0;
            }
            for (int i : ve)
            {
                if (vn[i] && ct2[i])
                    ans += siz[i];
                vn[i] = pn[i] = ct2[i] = first[i] = First[i] = 0;
            }
            putint(ans, '\n');
        }
        flush();
    }
}
int main()
{
    read(n);
    read(m);
    read(q);
    read(k);
    for (int i = 1, u, v; i <= m; ++i)
    {
        read(u);
        read(v);
        add(u, v);
    }
    work(1, n, 0);
    if (m == n - 1)
        sub::main();
    else
        rebuild(), sub::main();
    return 0;
}