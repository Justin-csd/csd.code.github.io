#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <random>
#include <ctime>

using namespace std;
const int N = 2e5 + 10, mod = 998244353;
int n, q, a[N];
char s[N];
inline int add(int x, int y) { return (x + y >= mod) ? x + y - mod : x + y; }
struct matrix
{
    int c[2][2];
    inline void init(int d)
    {
        c[0][0] = c[1][1] = d;
        c[0][1] = c[1][0] = 0;
    }
} W, E;
inline matrix operator*(const matrix &A, const matrix &B)
{
    matrix ret;
    ret.init(0);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            ret.c[i][j] = (1ll * A.c[i][0] * B.c[0][j] + 1ll * A.c[i][1] * B.c[1][j]) % mod;
    return ret;
}

int rt;
namespace Treap
{
    mt19937 rnd(time(0));
    matrix val[N][4], sum[N][4];
    // 0:A1->n 1:An->1 2:B1->n 3:Bn->1
    int tot, ran[N], ls[N], rs[N], rev[N], fl[N], siz[N];
    inline void pushup(int p)
    {
        siz[p] = siz[ls[p]] + siz[rs[p]] + 1;
        for (int i = 0; i < 4; ++i)
        {
            sum[p][i] = val[p][i];
            if (ls[p])
            {
                if (i & 1)
                    sum[p][i] = sum[p][i] * sum[ls[p]][i];
                else
                    sum[p][i] = sum[ls[p]][i] * sum[p][i];
            }
            if (rs[p])
            {
                if (i & 1)
                    sum[p][i] = sum[rs[p]][i] * sum[p][i];
                else
                    sum[p][i] = sum[p][i] * sum[rs[p]][i];
            }
        }
    }
    inline void rever(int p)
    {
        if (!p)
            return;
        rev[p] ^= 1;
        swap(sum[p][0], sum[p][1]);
        swap(sum[p][2], sum[p][3]);
        swap(ls[p], rs[p]);
    }
    inline void flip(int p)
    {
        if (!p)
            return;
        fl[p] ^= 1;
        for (int i = 0; i < 2; ++i)
            swap(val[p][i], val[p][i + 2]), swap(sum[p][i], sum[p][i + 2]);
    }
    inline void pushdown(int p)
    {
        if (rev[p])
        {
            rever(ls[p]);
            rever(rs[p]);
            rev[p] = 0;
        }
        if (fl[p])
        {
            flip(ls[p]);
            flip(rs[p]);
            fl[p] = 0;
        }
    }
    inline int newnode(int tp)
    {
        int p = ++tot;
        ran[p] = rnd();
        siz[p] = 1;
        val[p][0] = val[p][1] = sum[p][0] = sum[p][1] = tp ? W : E;
        val[p][2] = val[p][3] = sum[p][2] = sum[p][3] = tp ? E : W;
        return p;
    }
    inline int merge(int p1, int p2)
    {
        if (!p1 || !p2)
            return p1 + p2;
        pushdown(p1);
        pushdown(p2);
        if (ran[p1] < ran[p2])
        {
            rs[p1] = merge(rs[p1], p2);
            pushup(p1);
            return p1;
        }
        else
        {
            ls[p2] = merge(p1, ls[p2]);
            pushup(p2);
            return p2;
        }
    }
    inline void split(int p, int v, int &l, int &r)
    {
        if (!p)
        {
            l = r = 0;
            return;
        }
        pushdown(p);
        if (siz[ls[p]] + 1 <= v)
        {
            l = p;
            split(rs[p], v - siz[ls[p]] - 1, rs[p], r);
        }
        else
        {
            r = p;
            split(ls[p], v, l, ls[p]);
        }
        pushup(p);
    }
    inline void Flip(int l, int r)
    {
        int ql, pos, qr;
        split(rt, l - 1, ql, qr);
        split(qr, r - l + 1, pos, qr);
        flip(pos);
        rt = merge(merge(ql, pos), qr);
    }
    inline void Reverse(int l, int r)
    {
        int ql, pos, qr;
        split(rt, l - 1, ql, qr);
        split(qr, r - l + 1, pos, qr);
        rever(pos);
        rt = merge(merge(ql, pos), qr);
    }
}
using namespace Treap;

inline void solve()
{
    matrix now = sum[rt][1];
    printf("%d %d\n", now.c[0][0], add(now.c[0][0], now.c[0][1]));
}
int main()
{
    scanf("%d%d", &n, &q);
    scanf("%s", s + 1);
    W.c[0][0] = W.c[0][1] = W.c[1][1] = 1;
    W.c[1][0] = 0;
    E.c[0][0] = 2;
    E.c[0][1] = mod - 1;
    E.c[1][0] = 1;
    E.c[1][1] = 0;
    for (int i = 1; i <= n; ++i)
        rt = merge(rt, newnode(s[i] == 'W'));
    solve();
    while (q--)
    {
        scanf("%s", s + 1);
        if (s[1] == 'A')
        {
            scanf("%s", s + 1);
            rt = merge(rt, newnode(s[1] == 'W'));
        }
        else if (s[1] == 'F')
        {
            int l, r;
            scanf("%d%d", &l, &r);
            Flip(l, r);
        }
        else
        {
            int l, r;
            scanf("%d%d", &l, &r);
            Reverse(l, r);
        }
        solve();
    }
    return 0;
}