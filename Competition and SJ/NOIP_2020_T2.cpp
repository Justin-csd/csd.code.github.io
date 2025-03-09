#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = (1 << 20) + 1000;
//Failed in HACK
int T;

int n;
char s[N];

int Z[N];

void Z_algorithm()
{
    for (int i = 1; i <= n; i++)
        Z[i] = 0;
    for (int i = 2, l = 0, r = 0; i <= n; i++)
    {
        if (i <= r)
            Z[i] = min(Z[i - l + 1], r - i + 1);
        while (i + Z[i] <= n && s[1 + Z[i]] == s[i + Z[i]])
            Z[i]++;
        if (i + Z[i] - 1 > r)
            l = i, r = i + Z[i] - 1;
    }
}

int pre, suf, Fs;
int cnt[26];
bool flag1[26], flag2[26];

int cur1, cur2;
long long ans;

void work()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);

    Z_algorithm();

    memset(flag1, 0, sizeof(flag1));
    memset(flag2, 0, sizeof(flag2));
    for (int i = 1; i <= n; i++)
    {
        int ch = s[i] - 'a';
        flag2[ch] ^= 1;
    }

    Fs = 0;
    for (int i = 0; i < 26; i++)
        if (flag2[i])
            Fs++;

    pre = 0, suf = Fs;
    ans = 0, cur1 = cur2 = 0;
    memset(cnt, 0, sizeof(cnt));

    for (int i = 1; i < n; i++)
    {
        int ch = s[i] - 'a';

        flag1[ch] ^= 1, flag2[ch] ^= 1;

        if (flag1[ch])
            pre++;
        else
            pre--;

        if (flag2[ch])
            suf++, cur1 += cnt[suf];
        else
            cur1 -= cnt[suf], suf--;

        int k = min((Z[i + 1] / i) + 1, (n - 1) / i);
        int odd = (k + 1) / 2, even = k / 2;

        ans += 1ll * odd * cur1;
        ans += 1ll * even * cur2;

        cnt[pre]++;
        if (pre <= suf)
            cur1++;
        if (pre <= Fs)
            cur2++;
    }

    printf("%lld\n", ans);
}

int main()
{
    scanf("%d", &T);

    while (T--)
        work();

    return 0;
}