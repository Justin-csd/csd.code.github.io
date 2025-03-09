#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef unsigned long long ull;
int n1, n2;
ull nxt(ull x)
{
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}
ull hs[100010][2];
vector<int> g[100010][2];
bool cmp1(int a, int b)
{
    return hs[a][0] < hs[b][0];
}
bool cmp2(int a, int b)
{
    return hs[a][1] < hs[b][1];
}

int size[100010][2];
void dfs1(int x, int id)
{
    hs[x][id] = size[x][id] = 1;
    for (int v : g[x][id])
    {
        dfs1(v, id);
        hs[x][id] += nxt(hs[v][id]);
        size[x][id] += size[v][id];
    }
    if (id == 0)
        sort(g[x][id].begin(), g[x][id].end(), cmp1);
    else
        sort(g[x][id].begin(), g[x][id].end(), cmp2);
}
bool dfs(int x, int y)
{
    if (g[x][0].size() < g[y][1].size())
        return false;
    if (size[x][0] < size[y][1])
        return false;
    if (size[x][0] == size[y][1])
        return hs[x][0] == hs[y][1];
    vector<int> A, B;
    int a = 0, b = 0;
    while (a < g[x][0].size() && b < g[y][1].size())
    {
        if (hs[g[x][0][a]][0] == hs[g[y][1][b]][1])
            a++, b++;
        else if (hs[g[x][0][a]][0] < hs[g[y][1][b]][1])
            A.push_back(g[x][0][a]), a++;
        else
            B.push_back(g[y][1][b]), b++;
    }
    while (a < g[x][0].size())
        A.push_back(g[x][0][a]), a++;
    while (b < g[y][1].size())
        B.push_back(g[y][1][b]), b++;
    vector<int> p;
    for (int i = 0; i < A.size(); i++)
        p.push_back(i);
    do
    {
        bool jud = true;
        for (int i = 0; i < B.size(); i++)
        {
            if (size[A[p[i]]][0] < size[B[i]][1])
            {
                jud = false;
                break;
            }
        }
        if (!jud)
            continue;
        for (int i = 0; i < B.size(); i++)
        {
            if (!dfs(A[p[i]], B[i]))
            {
                jud = false;
                break;
            }
        }
        if (jud)
            return true;
    } while (next_permutation(p.begin(), p.end()));
    return false;
}
int main()
{
    int tim;
    scanf("%*d%d%*d", &tim);
    while (tim--)
    {
        scanf("%d", &n1);
        int rt1, rt2;
        for (int i = 1; i <= n1; i++)
        {
            int f;
            scanf("%d", &f);
            if (f == -1)
                rt1 = i;
            else
                g[f][0].push_back(i);
        }
        scanf("%d", &n2);
        for (int i = 1; i <= n2; i++)
        {
            int f;
            scanf("%d", &f);
            if (f == -1)
                rt2 = i;
            else
                g[f][1].push_back(i);
        }
        dfs1(rt1, 0);
        dfs1(rt2, 1);
        if (dfs(rt1, rt2))
            puts("Yes");
        else
            puts("No");
        for (int i = 1; i <= n1; i++)
            g[i][0].clear();
        for (int i = 1; i <= n2; i++)
            g[i][1].clear();
    }
}