#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
int n, m, lsh[1000010];
long long ans;
struct ques
{
    int l, r, val;
} q[1000010];
vector<pair<int, int>> v[1000010];
struct BIT
{
    int c[1000010];
#define lowbit(x) (x & -x)
    void update(int x)
    {
        while (x)
            c[x]++, x -= lowbit(x);
    }
    int query(int x)
    {
        int sum = 0;
        while (x <= m)
            sum += c[x], x += lowbit(x);
        return sum;
    }
} c;
int fa[1000010];
int find(int x)
{
    return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);
}
struct node
{
#define lson rt << 1
#define rson rt << 1 | 1
    int mn, pos, lz;
} tree[4000010];
void pushup(int rt)
{
    tree[rt].mn = min(tree[lson].mn, tree[rson].mn);
    if (tree[rt].mn == tree[lson].mn)
        tree[rt].pos = tree[lson].pos;
    else
        tree[rt].pos = tree[rson].pos;
}
void pushtag(int rt, int val)
{
    tree[rt].mn += val;
    tree[rt].lz += val;
}
void pushdown(int rt)
{
    if (tree[rt].lz)
    {
        pushtag(lson, tree[rt].lz);
        pushtag(rson, tree[rt].lz);
        tree[rt].lz = 0;
    }
}
void build(int rt, int l, int r)
{
    tree[rt].mn = tree[rt].lz = 0;
    tree[rt].pos = l;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
}
void update(int rt, int L, int R, int l, int r, int val)
{
    if (l <= L && R <= r)
    {
        pushtag(rt, val);
        return;
    }
    pushdown(rt);
    int mid = (L + R) >> 1;
    if (l <= mid)
        update(lson, L, mid, l, r, val);
    if (mid < r)
        update(rson, mid + 1, R, l, r, val);
    pushup(rt);
}
pair<int, int> query(int rt, int L, int R, int l, int r)
{
    if (l <= L && R <= r)
        return make_pair(tree[rt].mn, tree[rt].pos);
    pushdown(rt);
    int mid = (L + R) >> 1;
    pair<int, int> val = make_pair(0x3f3f3f3f, 0x3f3f3f3f);
    if (l <= mid)
        val = min(val, query(lson, L, mid, l, r));
    if (mid < r)
        val = min(val, query(rson, mid + 1, R, l, r));
    return val;
}
int val[1000010], mn[1000010];
void solve()
{
    scanf("%d%d", &n, &m);
    ans = 0;
    for (int i = 1; i <= n + 1; i++)
        fa[i] = i, val[i] = mn[i] = 0;
    for (int i = 1; i <= m; i++)
        c.c[i] = 0, v[i].clear();
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].val), lsh[i] = q[i].val;
    sort(lsh + 1, lsh + m + 1);
    for (int i = 1; i <= m; i++)
    {
        q[i].val = lower_bound(lsh + 1, lsh + m + 1, q[i].val) - lsh;
        v[q[i].val].push_back(make_pair(q[i].l, q[i].r));
    }
    for (int i = m; i >= 0; i--)
    {
        if (v[i].empty())
            continue;
        sort(v[i].begin(), v[i].end());
        int pre = n + 1;
        for (int j = v[i].size() - 1; j >= 0; j--)
        {
            if (v[i][j].second < pre)
            {
                int pos = find(v[i][j].first);
                if (pos > v[i][j].second)
                {
                    puts("-1");
                    return;
                }
                val[pos] = i;
                pre = pos;
            }
        }
        for (pair<int, int> p : v[i])
        {
            for (int j = find(p.first); j <= p.second; j = find(j))
                mn[j] = i, fa[j] = j + 1;
        }
    }
    build(1, 0, m + 1);
    for (int i = 1; i <= n; i++)
    {
        if (val[i])
        {
            ans += c.query(val[i] + 1);
            c.update(val[i]);
            update(1, 0, m + 1, val[i] + 1, m + 1, 1);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (val[i])
        {
            update(1, 0, m + 1, val[i] + 1, m + 1, -1);
            update(1, 0, m + 1, 0, val[i] - 1, 1);
        }
        else
        {
            pair<int, int> p = query(1, 0, m + 1, mn[i], m + 1);
            ans += p.first;
            if (p.second)
                update(1, 0, m + 1, 0, p.second - 1, 1);
        }
    }
    printf("%lld\n", ans);
}
int main()
{
    int tim;
    scanf("%d", &tim);
    while (tim--)
        solve();
    return 0;
}