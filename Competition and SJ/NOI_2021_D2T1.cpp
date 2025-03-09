#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned long long ull;
const int N = 400010, M = 65536;
int n, m, s[N][16], ct[M], a[16], lastans;
ull a1, a2;
char t[256];
vector<int> ve[16][M];
ull myRand(ull &k1, ull &k2)
{
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}
void gen(int n, ull a1, ull a2)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            int c = (myRand(a1, a2) & (1ull << 32)) ? 1 : 0;
            s[i][j >> 4] = (s[i][j >> 4] << 1) | c;
        }
        for (int j = 0; j < 16; ++j)
            ve[j][s[i][j]].push_back(i);
    }
}
int main()
{
    scanf("%d%d%llu%llu", &n, &m, &a1, &a2);
    gen(n, a1, a2);
    ct[0] = 0;
    for (int i = 1; i < M; ++i)
        ct[i] = ct[i ^ (i & (-i))] + 1;
    lastans = 0;
    for (int i = 1, k; i <= m; ++i)
    {
        scanf("%s", t);
        scanf("%d", &k);
        for (int j = 0; j < 16; ++j)
            a[j] = 0;
        for (int j = 0; j < 64; ++j)
        {
            int tmp = (t[j] >= '0' && t[j] <= '9') ? t[j] - '0' : t[j] - 'A' + 10;
            for (int k = 3; k >= 0; --k)
            {
                int c = ((tmp >> k) & 1) ^ lastans;
                a[j >> 2] = (a[j >> 2] << 1) | c;
            }
        }
        lastans = 0;
        for (int j = 0; j < 16 && !lastans; ++j)
        {
            for (int x : ve[j][a[j]])
            {
                int now = 0;
                for (int t = 0; t < 16 && now <= k; ++t)
                    now += ct[a[t] ^ s[x][t]];
                if (now <= k)
                {
                    lastans = 1;
                    break;
                }
            }
        }
        printf("%d\n", lastans);
    }
    return 0;
}