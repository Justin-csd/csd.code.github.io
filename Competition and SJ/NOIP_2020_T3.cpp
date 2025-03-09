#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

inline int read()
{
    int x = 0, f = 1;
    char s = getchar();
    while (s < '0' || s > '9')
    {
        if (s == '-')
            f = -f;
        s = getchar();
    }
    while (s >= '0' && s <= '9')
    {
        x = x * 10 + s - '0';
        s = getchar();
    }
    return x * f;
}

const int N = 60, M = 410;

int n, m;

int top[N], a[N][M];
int em;

int t;
pair<int, int> ans[820001];

void move(int x, int y)
{
    ans[++t] = make_pair(x, y);

    a[y][++top[y]] = a[x][top[x]--];
}

bool impx[M], impy[M];

int merge(int x, int y, int mid)
{
    int cx = 0, cy = 0;

    for (int i = 1; i <= m; i++)
        impx[i] = a[x][i] <= mid,
        impy[i] = a[y][i] <= mid;

    for (int i = 1; i <= m; i++)
        cx += impx[i], cy += impy[i];

    if (cx + cy > m)
    {
        cx = m - cx, cy = m - cy;

        for (int i = 1; i <= m; i++)
            impx[i] ^= 1, impy[i] ^= 1;
    }

    for (int i = 1; i <= m; i++)
        if (!impx[i] && cx + cy < m)
            impx[i] = 1, cx++;

    for (int i = cx; i; i--)
        move(y, em);

    for (int i = m; i; i--)
        if (impx[i])
            move(x, y);
        else
            move(x, em);

    for (int i = m - cx; i; i--)
        move(em, x);

    for (int i = cx; i; i--)
        move(y, x);

    for (int i = cx; i; i--)
        move(em, y);

    for (int i = cx; i; i--)
        move(x, em);

    for (int i = m; i; i--)
        if (impy[i])
            move(y, em);
        else
            move(y, x);

    int p = em;
    em = y;
    return p;
}

void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;

    vector<int> now;
    for (int i = 1; i <= n + 1; i++)
    {
        if (i == em)
            continue;
        if (l <= a[i][1] && a[i][1] <= r)
            now.push_back(i);
    }

    for (int i = 0; i + 1 < (int)now.size(); i++)
        now[i + 1] = merge(now[i], now[i + 1], mid);

    solve(l, mid), solve(mid + 1, r);
}

int main()
{
    n = read(), m = read();

    em = n + 1;

    for (int i = 1; i <= n; i++)
    {
        top[i] = m;
        for (int j = 1; j <= m; j++)
            a[i][j] = read();
    }

    solve(1, n);

    printf("%d\n", t);
    for (int i = 1; i <= t; i++)
        printf("%d %d\n", ans[i].first, ans[i].second);

    return 0;
}