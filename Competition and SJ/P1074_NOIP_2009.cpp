#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#define ll long long
using namespace std;
inline int read()
{
    int x = 0, o = 1;
    char ch = getchar();
    while (ch != '-' && (ch < '0' || ch > '9'))
        ch = getchar();
    if (ch == '-')
        o = -1, ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar();
    return x * o;
}
int a[10][10], hang[10][10], lie[10][10], ge[10][10];
int now, ans, tot, dfs[100][5];
struct node
{
    int num, sum;
} line[10];
inline bool cmp(node x, node y) { return x.sum < y.sum; }
inline int calc(int i, int j) { return (i - 1) / 3 * 3 + (j - 1) / 3 + 1; }
inline int point(int x, int y)
{
    if (x == 5 && y == 5)
        return 10;
    if (x >= 4 && x <= 6 && y >= 4 && y <= 6)
        return 9;
    if (x >= 3 && x <= 7 && y >= 3 && y <= 7)
        return 8;
    if (x >= 2 && x <= 8 && y >= 2 && y <= 8)
        return 7;
    return 6;
}
inline void DFS(int ord, int has)
{
    if (ord > tot)
    {
        if (has > ans)
            ans = has;
        return;
    }
    for (int i = 1; i <= 9; ++i)
    {
        if (hang[dfs[ord][1]][i])
            continue;
        if (lie[dfs[ord][2]][i])
            continue;
        if (ge[dfs[ord][3]][i])
            continue;
        hang[dfs[ord][1]][i] = 1;
        lie[dfs[ord][2]][i] = 1;
        ge[dfs[ord][3]][i] = 1;
        DFS(ord + 1, has + dfs[ord][4] * i);
        hang[dfs[ord][1]][i] = 0;
        lie[dfs[ord][2]][i] = 0;
        ge[dfs[ord][3]][i] = 0;
    }
}
int main()
{
    for (int i = 1; i <= 9; ++i)
        line[i].num = i;
    for (int i = 1; i <= 9; ++i)
        for (int j = 1; j <= 9; ++j)
        {
            a[i][j] = read();
            if (!a[i][j])
            {
                ++line[i].sum;
                continue;
            }
            hang[i][a[i][j]] = 1;
            lie[j][a[i][j]] = 1;
            ge[calc(i, j)][a[i][j]] = 1;
            now += point(i, j) * a[i][j];
        }
    sort(line + 1, line + 9 + 1, cmp);
    for (int i = 1; i <= 9; ++i)
        for (int j = 1; j <= 9; ++j)
        {
            if (a[line[i].num][j])
                continue;
            dfs[++tot][1] = line[i].num;
            dfs[tot][2] = j;
            dfs[tot][3] = calc(line[i].num, j);
            dfs[tot][4] = point(line[i].num, j);
        }
    DFS(1, now);
    if (!ans)
        puts("-1");
    else
        printf("%d\n", ans);
    return 0;
}