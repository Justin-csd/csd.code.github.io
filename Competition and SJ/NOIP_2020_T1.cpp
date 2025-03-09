#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

#define u128 __int128

using namespace std;

inline void print(u128 x)
{
    if (x > 9)
        print(x / 10);
    putchar('0' + x % 10);
}

u128 gcd(u128 a, u128 b)
{
    if (!b)
        return a;
    return gcd(b, a % b);
}

const int N = 400100;

struct Node
{
    u128 x, y;
} a[N];

Node operator+(Node a, Node b)
{
    Node c;
    c.y = a.y * b.y;
    c.x = a.x * b.y + b.x * a.y;
    u128 S = gcd(c.x, c.y);

    if (!S)
    {
        c.x = 0;
        c.y = 1;
    }
    else
    {
        c.x /= S;
        c.y /= S;
    }

    return c;
}

Node operator/(Node a, int num)
{
    Node b;
    b.x = a.x;
    b.y = 1ll * a.y * num;
    u128 S = gcd(b.x, b.y);

    if (!S)
    {
        b.x = 0;
        b.y = 1;
    }
    else
    {
        b.x /= S;
        b.y /= S;
    }

    return b;
}

int n, m;

vector<int> to[N];

int deg[N];

void topsort()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            q.push(i);

    while (q.size())
    {
        int u = q.front();
        q.pop();
        if (to[u].size() == 0)
            continue;
        Node give = a[u] / to[u].size();
        for (int i = 0; i < (int)to[u].size(); i++)
        {
            int v = to[u][i];
            a[v] = a[v] + give;
            if (--deg[v] == 0)
                q.push(v);
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);

    for (int i = 1, S; i <= n; i++)
    {
        scanf("%d", &S);

        while (S--)
        {
            int x;
            scanf("%d", &x);
            to[i].push_back(x);
        }
    }

    for (int i = 1; i <= m; i++)
        a[i].x = 1, a[i].y = 1;

    for (int i = m + 1; i <= n; i++)
        a[i].x = 0, a[i].y = 1;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j < (int)to[i].size(); j++)
        {
            int v = to[i][j];
            deg[v]++;
        }

    topsort();

    for (int i = 1; i <= n; i++)
        if (to[i].size() == 0)
        {
            print(a[i].x);
            printf(" ");
            print(a[i].y);
            puts("");
        }

    return 0;
}