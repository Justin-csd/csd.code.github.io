#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
#define merge(x, y) dad[father(x)] = father(y)
#define check(x, y) (father(x) == father(y))
#define cl(x) memset(x, 0, sizeof(x))
#define inf 2000000001

template <typename _Tp>
inline void read(_Tp &x)
{
    char c11 = getchar();
    x = 0;
    bool booo = 0;
    while (c11 < '0' || c11 > '9')
    {
        if (c11 == '-')
            booo = 1;
        c11 = getchar();
    }
    while (c11 >= '0' && c11 <= '9')
    {
        x = x * 10 + c11 - '0';
        c11 = getchar();
    }
    if (booo)
        x = -x;
    return;
}

const int maxn = 10050, maxm = 50050;
struct so
{
    int l, r, w;
    bool bo;
} a[maxm];
long long dad[maxn], mi[maxn][20], n, m, h;
struct node
{
    long long next, v, w;
} b[maxm << 2];
long long p = 0, head[maxn];
long long depth[maxn], anc[maxn][20], maxlog;
long long str[maxn], stt = 0;

inline long long father(long long x)
{
    if (!dad[x])
        return x;
    return dad[x] = father(dad[x]);
}
inline bool my_comp(const so aa, const so bb) { return aa.w > bb.w; }
void init_k();
void work_k();
void ex();
void add(long long, long long, long long);
void dfs(long long, long long, long long, long long);

long long lca(long long x, long long y)
{
    if (!(father(x) == father(y)))
        return -1;
    long long ans = inf;
    if (depth[x] < depth[y])
        swap(x, y);

    if (depth[x] != depth[y])
        for (long long i = maxlog; i > -1; i--)
            if (depth[y] <= depth[anc[x][i]])
            {
                ans = min(ans, mi[x][i]);
                x = anc[x][i];
            }
    if (x == y)
        return ans;

    for (long long i = maxlog; i > -1; i--)
        if (anc[x][i] != anc[y][i])
        {
            ans = min(ans, mi[x][i]);
            x = anc[x][i];
            ans = min(ans, mi[y][i]);
            y = anc[y][i];
        }
    return min(min(ans, mi[x][0]), mi[y][0]);
}

void query()
{
    maxlog = (log(n) / log(2)) + 3;
    long long T;
    read(T);
    long long A, B;
    for (long long i = 1; i <= T; i++)
    {
        read(A);
        read(B);
        printf("%lld\n", lca(A, B));
    }
    return;
}

/***************************************************/
int main()
{

    cl(dad);
    cl(head);
    cl(depth);

    init_k();

    work_k();

    ex();

    for (long long i = 1; i <= stt; i++)
        dfs(str[i], 0, 1, inf);

    query();

    return 0;
}
/***************************************************/
void dfs(long long x, long long last, long long deep, long long zhi)
{
    depth[x] = deep;
    anc[x][0] = last;
    mi[x][0] = zhi;
    for (long long i = 1; i <= 15; i++)
    {
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
        mi[x][i] = min(zhi, min(mi[x][i - 1], mi[anc[x][i - 1]][i - 1]));
    }
    for (long long i = head[x]; i; i = b[i].next)
        if (b[i].v != last)
        {
            long long v = b[i].v;
            dfs(v, x, deep + 1, b[i].w);
        }
}

void add(long long u, long long v, long long w)
{
    b[++p].v = v;
    b[p].w = w;
    b[p].next = head[u];
    head[u] = p;
}

void ex()
{
    for (long long i = 1; i <= m; i++)
        if (a[i].bo)
        {
            add(a[i].l, a[i].r, a[i].w);
            add(a[i].r, a[i].l, a[i].w);
        }

    for (long long i = 0; i <= n; i++)
        for (long long j = 0; j <= 15; j++)
            mi[i][j] = inf;
    return;
}

void work_k()
{
    set<long long> csdn;
    sort(a + 1, a + m + 1, my_comp);
    h = 0;
    for (long long i = 1; i <= m; i++)
    {
        if (!check(a[i].l, a[i].r))
        {
            merge(a[i].l, a[i].r);
            a[i].bo = 1;
            h++;
        }
        if (h == n - 1)
            break;
    }
    for (long long i = 1; i <= n; i++)
    {
        long long fa = father(i);
        if (!csdn.count(fa))
        {
            csdn.insert(fa);
            str[++stt] = i;
        }
    }
    return;
}

void init_k()
{
    read(n);
    read(m);
    for (long long i = 1; i <= m; i++)
    {
        read(a[i].l);
        read(a[i].r);
        read(a[i].w);
        a[i].bo = 0;
    }
    return;
}