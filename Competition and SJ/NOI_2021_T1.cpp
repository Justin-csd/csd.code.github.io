#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
namespace iobuff
{
    const int LEN = 10000000;
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
    inline void putint(T x, char div = '\n')
    {
        static char s[15];
        static int top;
        top = 0;
        while (x)
            s[top++] = x % 10, x /= 10;
        !top ? pc('0'), 0 : 0;
        while (top--)
            pc(s[top] + '0');
        pc(div);
    }
}
using namespace iobuff;
const int N = 1e5 + 10;
struct node
{
    int v, nxt;
} e[N << 1];
int T, n, m, tot, first[N], cnt, fa[N], siz[N], dep[N], son[N], top[N], pos[N], num[N];
inline void add(int u, int v)
{
    e[++cnt].v = v;
    e[cnt].nxt = first[u];
    first[u] = cnt;
}
void dfs(int u, int f)
{
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    son[u] = 0;
    for (int i = first[u]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (v ^ f)
        {
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]])
                son[u] = v;
        }
    }
}
void hld(int u, int tp)
{
    top[u] = tp;
    pos[u] = ++tot;
    num[tot] = u;
    if (son[u])
        hld(son[u], tp);
    for (int i = first[u]; i; i = e[i].nxt)
        if (e[i].v != fa[u] && e[i].v != son[u])
            hld(e[i].v, e[i].v);
}

namespace SGT
{
#define lc (p << 1)
#define rc (p << 1 | 1)
#define mid ((l + r) >> 1)
    const int M = N << 2;
    int L[M], R[M], sum[M], tag[M];
    inline void cover(int p, int l, int r, int c)
    {
        tag[p] = L[p] = R[p] = c;
        sum[p] = r - l;
    }
    inline void pushup(int p)
    {
        sum[p] = sum[lc] + sum[rc] + (R[lc] == L[rc]);
        R[p] = R[rc];
        L[p] = L[lc];
    }
    inline void pushdown(int p, int l, int r)
    {
        if (!tag[p])
            return;
        if (lc)
            cover(lc, l, mid, tag[p]);
        if (rc)
            cover(rc, mid + 1, r, tag[p]);
        tag[p] = 0;
    }
    void init(int p = 1, int l = 1, int r = n)
    {
        sum[p] = tag[p] = 0;
        if (l == r)
        {
            L[p] = R[p] = l;
            return;
        }
        init(lc, l, mid);
        init(rc, mid + 1, r);
        pushup(p);
    }
    void modify(int p, int ql, int qr, int c, int l = 1, int r = n)
    {
        if (ql <= l && r <= qr)
        {
            cover(p, l, r, c);
            return;
        }
        pushdown(p, l, r);
        if (ql <= mid)
            modify(lc, ql, qr, c, l, mid);
        if (qr > mid)
            modify(rc, ql, qr, c, mid + 1, r);
        pushup(p);
    }
    int query(int p, int ql, int qr, int l = 1, int r = n)
    {
        if (ql <= l && r <= qr)
            return sum[p];
        if (tag[p])
            return min(qr, r) - max(ql, l);
        pushdown(p, l, r);
        int ans = 0;
        if (ql <= mid)
            ans += query(lc, ql, qr, l, mid);
        if (qr > mid)
            ans += query(rc, ql, qr, mid + 1, r);
        if (ql <= mid && qr > mid)
            ans += (R[lc] == L[rc]);
        return ans;
    }
    int getcol(int p, int x, int l = 1, int r = n)
    {
        if (l == r)
            return R[p];
        pushdown(p, l, r);
        return x <= mid ? getcol(lc, x, l, mid) : getcol(rc, x, mid + 1, r);
    }
}

int col;
inline void modify(int u, int v)
{
    ++col;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        SGT::modify(1, pos[top[u]], pos[u], col);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    SGT::modify(1, pos[u], pos[v], col);
}
inline int query(int u, int v)
{
    int ans = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        if (top[u] != u)
            ans += SGT::query(1, pos[top[u]], pos[u]);
        int x = SGT::getcol(1, pos[top[u]]), y = SGT::getcol(1, pos[fa[top[u]]]);
        if (x == y && x != 0)
            ans++;
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    if (u != v)
        ans += SGT::query(1, pos[u], pos[v]);
    return ans;
}

int main()
{
    read(T);
    while (T--)
    {
        read(n);
        read(m);
        cnt = 0;
        memset(first + 1, 0, sizeof(int) * (n));
        for (int i = 1, u, v; i < n; ++i)
        {
            read(u);
            read(v);
            add(u, v);
            add(v, u);
        }
        tot = 0;
        col = n;
        dfs(1, 0);
        hld(1, 1);
        SGT::init();
        while (m--)
        {
            int op, a, b;
            read(op);
            read(a);
            read(b);
            if (op == 1)
                modify(a, b);
            else
                putint(query(a, b), '\n');
        }
    }
    flush();
    return 0;
}