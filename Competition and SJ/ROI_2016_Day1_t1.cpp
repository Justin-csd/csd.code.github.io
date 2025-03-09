#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef double db;
#define pb push_back
#define rep(i, a, b) for (int i = a, i##end = b; i <= i##end; ++i)
char buf[200000], *p1, *p2;
#define getchar() (((p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, 200000, stdin))), *p1++)
char IO;
//人烟之山
int rd()
{
    int s = 0;
    int f = 0;
    while (!isdigit(IO = getchar()))
        f |= IO == '-';
    do
        s = (s << 1) + (s << 3) + (IO ^ '0');
    while (isdigit(IO = getchar()));
    return f ? -s : s;
}

const int N = 4e5 + 10, U = 1e9 + 10;

int n, m, K[N], X[N], L[N], R[N];
ll Y[N];
struct Que
{
    int x, y, id;
    bool operator<(const Que __) const
    {
        return x < __.x;
    }
} Q[N];
struct Node
{
    int k;
    ll b;
    ll operator[](const ll x) const
    {
        return 1ll * k * x + b;
    }
    friend db Cross(Node x, Node y) { return 1.0 * (y.b - x.b) / (x.k - y.k); }
    bool operator<(const Node __) const
    {
        return k < __.k || (k == __.k && b < __.b);
    }
};
vector<Node> H[N << 2];
vector<Node>::iterator P[N << 2];
void Build(int p, int l, int r)
{
    if (l == r)
        return H[p].pb((Node){K[l], Y[l] - 1ll * K[l] * X[l]}), P[p] = H[p].begin(), void();
    int mid = (l + r) >> 1;
    Build(p << 1, l, mid), Build(p << 1 | 1, mid + 1, r);
    int p1 = 0, s1 = H[p << 1].size(), p2 = 0, s2 = H[p << 1 | 1].size(), R = -1;
    auto Ins = [&] (Node L)
    {
        while (~R && H[p][R].b <= L.b)
            R--, H[p].pop_back();
        while (R > 0 && Cross(H[p][R], H[p][R - 1]) >= Cross(H[p][R], L) - 1e-8)
            R--, H[p].pop_back();
        H[p].pb(L), R++;
    };
    while (p1 < s1 || p2 < s2)
    {
        if (p1 < s1 && (p2 == s2 || H[p << 1][p1] < H[p << 1 | 1][p2]))
            Ins(H[p << 1][p1++]);
        else
            Ins(H[p << 1 | 1][p2++]);
    }
    P[p] = H[p].begin();
}

ll Que(int p, int x)
{
    while (P[p] + 1 != H[p].end() && (*(P[p] + 1))[x] >= (*P[p])[x])
        P[p]++;
    return (*P[p])[x];
}
int QueL(int p, int l, int r, int x, int qx, int y)
{
    if (x < l || Que(p, qx) <= y)
        return 0;
    if (l == r)
        return l;
    int mid = (l + r) >> 1, t;
    if (x > mid && (t = QueL(p << 1 | 1, mid + 1, r, x, qx, y)))
        return t;
    return QueL(p << 1, l, mid, x, qx, y);
}
int QueR(int p, int l, int r, int x, int qx, int y)
{
    if (x > r || Que(p, qx) <= y)
        return n + 1;
    if (l == r)
        return l;
    int mid = (l + r) >> 1, t;
    if (x <= mid && (t = QueR(p << 1, l, mid, x, qx, y)) <= n)
        return t;
    return QueR(p << 1 | 1, mid + 1, r, x, qx, y);
}

int main()
{
    n = rd(), m = rd();
    rep(i, 1, n)
    {
        X[i] = X[i - 1] + rd(), K[i] = rd();
        Y[i] = Y[i - 1] + 1ll * (X[i] - X[i - 1]) * K[i];
    }
    rep(i, 1, m) Q[i].x = rd(), Q[i].y = rd(), Q[i].id = i;
    sort(Q + 1, Q + m + 1);
    Build(1, 1, n);
    int p = 1;
    rep(i, 1, m)
    {
        while (p <= n && X[p] < Q[i].x)
            p++;
        L[Q[i].id] = QueL(1, 1, n, p - 1, Q[i].x, Q[i].y);
        R[Q[i].id] = QueR(1, 1, n, p + (X[p] == Q[i].x), Q[i].x, Q[i].y);
    }
    rep(i, 1, m) printf("%d %d\n", X[L[i]], X[R[i] - 1]);
}