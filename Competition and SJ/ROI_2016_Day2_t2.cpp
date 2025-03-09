#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <cstring>
#define MIT multiset<node>::iterator
using namespace std;
const int MAXN = 2e5 + 5;
int n, K, st[21][MAXN], lg[MAXN], td, dfn[MAXN], ed[MAXN], dep[MAXN];
int U[MAXN], V[MAXN], ansl, ansr, mx[2][MAXN];
int Ans;
vector<int> e[MAXN];
//快递
struct node
{
    int p, id;
    bool operator<(const node &x) const
    {
        return dfn[p] != dfn[x.p] ? dfn[p] < dfn[x.p] : id < x.id;
    }
};
vector<node> Add[MAXN], Del[MAXN];
multiset<node> S[MAXN];

void dfs(int p, int fa)
{
    st[0][td] = fa;
    dfn[p] = ++td;
    dep[p] = dep[fa] + 1;
    for (int v : e[p])
        if (v != fa)
            dfs(v, p);
    ed[p] = td;
}
bool in(int u, int v) { return dfn[u] <= dfn[v] && ed[v] <= ed[u]; }
int Min(int x, int y) { return dfn[x] <= dfn[y] ? x : y; }
int MIN(int x, int y) { return dep[x] >= dep[y] ? x : y; }
void init()
{
    for (int i = 2; i <= td; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int j = 1; j <= lg[td]; ++j)
        for (int i = 1; i + (1 << j) - 1 < td; ++i)
            st[j][i] = Min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
}
int Q(int x, int y)
{
    if (x == y)
        return x;
    x = dfn[x];
    y = dfn[y];
    if (x > y)
        swap(x, y);
    --y;
    int k = lg[y - x + 1];
    return Min(st[k][x], st[k][y - (1 << k) + 1]);
}
int dist(int x, int y) { return dep[x] + dep[y] - dep[Q(x, y)] * 2; }
void Upd_Ans(int x, int y)
{
    int u1 = U[x], u2 = U[y], v1 = V[x], v2 = V[y], lca = Q(u1, v1);
    if (x == y)
        return;
    if (!in(Q(u2, v2), lca))
        return;
    if (!in(lca, u2) && !in(lca, v2))
        return;
    int u = MIN(Q(u1, u2), Q(u1, v2)), v = MIN(Q(v1, v2), Q(v1, u2));
    if (dist(u, v) > Ans)
    {
        Ans = dist(u, v);
        ansl = x;
        ansr = y;
    }
}
int Get_lca(int id) { return id == 0 ? 0 : Q(U[id], V[id]); }
void Upd(int p, int id)
{
    if (id == 0 || mx[0][p] == id || mx[1][p] == id)
        return;
    int m0 = mx[0][p], m1 = mx[1][p];
    if (dep[Get_lca(m1)] > dep[Get_lca(id)])
        m1 = id;
    if (dep[Get_lca(m0)] > dep[Get_lca(m1)])
        swap(m1, m0);
    mx[0][p] = m0;
    mx[1][p] = m1;
}

void Get_mx(int p, int fa)
{
    for (int v : e[p])
        if (v != fa)
        {
            Get_mx(v, p);
            Upd(p, mx[0][v]);
            Upd(p, mx[1][v]);
        }
    Upd_Ans(mx[0][p], mx[1][p]);
    Upd_Ans(mx[1][p], mx[0][p]);
}

void Insert(int p, node x)
{
    MIT it = S[p].lower_bound(x);
    if (it != S[p].end())
        Upd_Ans(x.id, it->id), Upd_Ans(it->id, x.id);
    if (it != S[p].begin())
        --it, Upd_Ans(x.id, it->id), Upd_Ans(x.id, it->id);
    S[p].insert(x);
}

void solve(int p, int fa)
{
    for (int v : e[p])
    {
        if (v != fa)
        {
            solve(v, p);
            if (S[v].size() > S[p].size())
                swap(S[p], S[v]);
            for (node i : S[v])
                Insert(p, i);
        }
    }
    for (node i : Add[p])
        Insert(p, i);
    for (node i : Del[p])
        S[p].erase(S[p].find(i));
}

int main()
{
    //	freopen("tree.in","r",stdin);
    //	freopen("tree.out","w",stdout);
    scanf("%d %d", &n, &K);
    for (int i = 2; i <= n; ++i)
    {
        int fa;
        scanf("%d", &fa);
        e[fa].push_back(i);
        e[i].push_back(fa);
    }
    dfs(1, 0);
    init();
    ansl = 1;
    ansr = 2;
    dep[0] = n + 1;
    for (int i = 1; i <= K; ++i)
    {
        scanf("%d %d", &U[i], &V[i]);
        int lca = Q(U[i], V[i]);
        Add[U[i]].push_back(node{V[i], i});
        Add[V[i]].push_back(node{U[i], i});
        Del[lca].push_back(node{U[i], i});
        Del[lca].push_back(node{V[i], i});
        Upd(U[i], i);
        Upd(V[i], i);
    }
    Get_mx(1, 0);
    solve(1, 0);
    printf("%d\n%d %d\n", Ans, ansl, ansr);
    return 0;
}