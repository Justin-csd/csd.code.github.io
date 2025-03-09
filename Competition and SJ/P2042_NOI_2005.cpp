#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define N 500005
#define ll long long
#define ls(x) tr[x].l
#define rs(x) tr[x].r
using namespace std;
int n, m, T;
const int inf = 1e9;
struct vals
{
    int sum, lmax, rmax, maxx;
    void fill(int x, int l)
    {
        sum = x * l;
        maxx = lmax = rmax = max(x * l, x);
    }
    void rev()
    {
        swap(lmax, rmax);
    }
};
struct tnode
{
    int l, r, siz;
    vals w;
    int rev, cov;
};
vals operator*(vals a, vals b)
{
    return (vals){
        a.sum + b.sum,
        max(a.lmax, b.lmax + a.sum),
        max(b.rmax, a.rmax + b.sum),
        max(a.maxx, max(b.maxx, a.rmax + b.lmax))};
}
int rt;
struct segtree
{
    tnode tr[N * 2];
    int buc[N * 2], top, tot;
    inline int gnode()
    {
        int id = top ? buc[top--] : ++tot;
        tr[id] = {0};
        tr[id].cov = inf;
        return id;
    }
    void Pushup(int x)
    {
        tr[x].w = tr[ls(x)].w * tr[rs(x)].w;
        tr[x].siz = tr[ls(x)].siz + tr[rs(x)].siz;
    }
    void Pushdown(int x)
    {
        if (tr[x].rev)
        {
            tr[ls(x)].rev ^= 1;
            tr[rs(x)].rev ^= 1;
            tr[ls(x)].w.rev();
            tr[rs(x)].w.rev();
            swap(ls(ls(x)), rs(ls(x)));
            swap(ls(rs(x)), rs(rs(x)));
            tr[x].rev = 0;
        }
        if (tr[x].cov != inf)
        {
            tr[ls(x)].w.fill(tr[x].cov, tr[ls(x)].siz);
            tr[rs(x)].w.fill(tr[x].cov, tr[rs(x)].siz);
            tr[ls(x)].cov = tr[rs(x)].cov = tr[x].cov;
            tr[x].cov = inf;
        }
    }
    int merges(int l, int r)
    {
        int x = gnode();
        ls(x) = l, rs(x) = r;
        Pushup(x);
        return x;
    }
    void build(int &u, int l, int r, int *a)
    {
        u = gnode();
        tr[u].cov = inf;
        if (l == r)
        {
            tr[u].w.fill(a[l], 1);
            tr[u].siz = 1;
            return;
        }
        int mid = (l + r) / 2;
        build(ls(u), l, mid, a);
        build(rs(u), mid + 1, r, a);
        Pushup(u);
    }
    int bl[N], bm[N], br[N], dl, dm, dr;
    void split(int u, int l, int r, int L, int R)
    {
        if (r < L)
        {
            bl[++dl] = u;
            return;
        }
        if (l > R)
        {
            br[++dr] = u;
            return;
        }
        if (l >= L && r <= R)
        {
            bm[++dm] = u;
            return;
        }
        int mid = l - 1 + tr[ls(u)].siz;
        Pushdown(u);
        split(ls(u), l, mid, L, R);
        split(rs(u), mid + 1, r, L, R);
        buc[++top] = u;
    }
    int w, p[N];
    void mergeall()
    {
        while (w > 1)
        {
            for (int i = 2; i <= w; i += 2)
                p[i / 2] = merges(p[i - 1], p[i]);
            if (w & 1)
                p[(w + 1) / 2] = p[w];
            w = (w + 1) / 2;
        }
        rt = p[1];
    }
    void dfs(int now)
    {
        if (!now)
            return;
        buc[++top] = now;
        dfs(ls(now)), dfs(rs(now));
    }
    void del(int l, int r)
    {
        dl = dm = dr = w = 0;
        split(rt, 1, n, l, r);
        for (int i = 1; i <= dl; i++)
            p[++w] = bl[i];
        for (int i = 1; i <= dm; i++)
            dfs(bm[i]);
        for (int i = 1; i <= dr; i++)
            p[++w] = br[i];
        mergeall();
        n -= r - l + 1;
    }
    void reverse(int l, int r)
    {
        dl = dm = dr = w = 0;
        split(rt, 1, n, l, r);
        for (int i = 1; i <= dl; i++)
            p[++w] = bl[i];
        for (int i = dm; i >= 1; i--)
        {
            p[++w] = bm[i];
            swap(ls(bm[i]), rs(bm[i]));
            tr[bm[i]].rev ^= 1;
            tr[bm[i]].w.rev();
        }
        for (int i = 1; i <= dr; i++)
            p[++w] = br[i];
        mergeall();
    }
    void ins(int *a, int m, int pos)
    {
        dl = dm = dr = w = 0;
        for (int i = 1; i <= m; i++)
            scanf("%d", &a[i]);
        int tmp = 0;
        build(tmp, 1, m, a);
        split(rt, 1, n, pos, pos);
        for (int i = 1; i <= dl; i++)
            p[++w] = bl[i];
        for (int i = 1; i <= dm; i++)
            p[++w] = bm[i];
        p[++w] = tmp;
        for (int i = 1; i <= dr; i++)
            p[++w] = br[i];
        mergeall();
        n += m;
    }
    void modify(int u, int l, int r, int L, int R, int v)
    {
        if (l > R || r < L)
            return;
        if (l >= L && r <= R)
        {
            tr[u].cov = v;
            tr[u].w.fill(v, r - l + 1);
            return;
        }
        int mid = l + tr[ls(u)].siz - 1;
        Pushdown(u);
        modify(ls(u), l, mid, L, R, v);
        modify(rs(u), mid + 1, r, L, R, v);
        Pushup(u);
    }
    int query(int u, int l, int r, int L, int R)
    {
        if (l > R || r < L)
            return 0;
        if (l >= L && r <= R)
            return tr[u].w.sum;
        int mid = l + tr[ls(u)].siz - 1;
        Pushdown(u);
        return query(ls(u), l, mid, L, R) + query(rs(u), mid + 1, r, L, R);
    }
} tr;
int a[N];
char opr[12];
int main()
{
    //	freopen("P2042_2.in","r",stdin);
    //	freopen("m.txt","w",stdout);
    scanf("%d%d", &n, &T);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    tr.build(rt, 1, n, a);
    while (T--)
    {
        int tot, l, r, w;
        scanf("%s", opr + 1);
        if (opr[3] ^ 'X')
            scanf("%d%d", &l, &tot), r = l + tot - 1;
        if (opr[1] == 'I')
            tr.ins(a, tot, l);
        if (opr[1] == 'D')
            tr.del(l, r);
        if (opr[3] == 'K')
            scanf("%d", &w), tr.modify(rt, 1, n, l, r, w);
        if (opr[1] == 'R')
            tr.reverse(l, r);
        if (opr[1] == 'G')
            printf("%d\n", tr.query(rt, 1, n, l, r));
        if (opr[3] == 'X')
            printf("%d\n", tr.tr[rt].w.maxx);
    }
    return 0;
}