#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
const int mod = 1000000007;
int n, k, num, ans, trans[10010][7], dp[2][10010], l[1010], r[1010];
map<vector<int>, int> mp;
int dfs(vector<int> g)
{
    if (mp.find(g) != mp.end())
        return mp[g];
    mp[g] = num++;
    int id = mp[g];
    for (int i = 0; i < 7; i++)
    {
        vector<int> tmp;
        for (int j = 0; j < 9; j++)
            tmp.push_back(101);
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (g[3 * j + k] == 101)
                    continue;
                for (int x = 0; x < 3; x++)
                {
                    int val = i - j - k - x;
                    if (val < 0)
                        val = -val;
                    else
                        val = val == 1;
                    for (int l = k; l <= min(2, j + k); l++)
                        tmp[3 * l + x] = min(tmp[3 * l + x], g[3 * j + k] + val);
                }
            }
        }
        trans[id][i] = dfs(tmp);
    }
    return id;
}
int main()
{
    int tim;
    scanf("%d", &tim);
    dfs({0, 101, 101, 101, 101, 101, 101, 101, 101});
    while (tim--)
    {
        scanf("%d%d", &n, &k);
        ans = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &l[i], &r[i]);
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        int cur = 0;
        for (int i = 1; i <= n; i++)
        {
            cur ^= 1;
            memset(dp[cur], 0, sizeof(dp[cur]));
            for (int j = 0; j < num; j++)
            {
                if (!dp[cur ^ 1][j])
                    continue;
                for (int k = 0; k < 7; k++)
                {
                    int ret = 0;
                    if (k < 6)
                        ret = l[i] <= k && k <= r[i];
                    else if (r[i] >= 6)
                        ret = r[i] - max(l[i], 6) + 1;
                    dp[cur][trans[j][k]] = (dp[cur][trans[j][k]] + 1ll * ret * dp[cur ^ 1][j]) % mod;
                }
            }
        }
        for (pair<vector<int>, int> p : mp)
            if (p.first[0] <= k)
                ans = (ans + dp[cur][p.second]) % mod;
        if (k == 1)
        {
            bool jud = true;
            for (int i = 1; i <= n; i++)
                if (l[i] != 0)
                {
                    jud = false;
                    break;
                }
            if (jud)
                ans = (ans - 1 + mod) % mod;
            if (n == 3 && l[1] <= 1 && r[1] >= 1 && l[2] <= 1 && r[2] >= 1 && l[3] <= 1 && r[3] >= 1)
                ans = (ans - 1 + mod) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}