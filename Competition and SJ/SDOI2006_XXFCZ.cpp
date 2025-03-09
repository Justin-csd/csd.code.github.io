#include "bits/stdc++.h"
using namespace std;
typedef long double lb;
const int N = 52;
const lb eps = 1e-8;
int n;
lb f[N][N];
lb ans[N];
int fl;
bool vis[N];
int guass()
{
    for (int i = 1; i <= n; i++)
    {
        int id = i;
        bool find = false;
        for (int j = 1; j <= n; j++)
        {
            if (vis[j] == 0 && fabs(f[j][i]) > fabs(f[id][i]))
            {
                id = j;
            }
        }
        if (fabs(f[id][i]) >= eps)
            find = true;
        if (id != i)
        {
            for (int j = 1; j <= n + 1; j++)
            {
                swap(f[id][j], f[i][j]);
            }
        }
        if (find)
        {
            vis[i] = true;
            for (int j = 1; j <= n; j++)
            {
                if (j == i)
                    continue;
                lb ch = f[j][i] / f[i][i];
                for (int k = 1; k <= n + 1; k++)
                {
                    f[j][k] = f[j][k] - ch * f[i][k];
                }
            }
        }
    }
    int wq = 0, wj = 0;
    for (int i = 1; i <= n; i++)
    {
        int j = 1;
        while (fabs(f[i][j]) < eps && j <= n + 1)
            j++;
        if (j > n + 1)
            wq = 1;
        if (j == n + 1)
            wj = 1;
    }
    if (wj)
    {
        return -1;
    }
    if (wq)
    {
        return 0;
    }

    for (int i = n; i >= 1; i--)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;
            f[i][n + 1] -= f[i][j] * ans[j];
        }
        ans[i] = f[i][n + 1] / f[i][i] + eps;
    }
    return 1;
}
int main()
{
    scanf("%d", &n);
    lb k;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n + 1; j++)
        {
            scanf("%Lf", &f[i][j]);
        }
    }
    fl = 0;
    fl = guass();
    if (fl != 1)
    {
        printf("%d", fl);
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        printf("x%d=%.2Lf\n", i, ans[i]);
    }
    return 0;
}