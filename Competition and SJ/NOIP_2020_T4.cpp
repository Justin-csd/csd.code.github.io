#include <cstdio>
#include <cstring>
#include <algorithm>

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

int power(int a, int b, int p)
{
    int ans = 1;
    for (; b; b >>= 1)
    {
        if (b & 1)
            ans = 1ll * ans * a % p;
        a = 1ll * a * a % p;
    }
    return ans;
}

const int N = 500100, SIZE = 20;
const int mod = 1e9 + 7;

int n, k;

int w[SIZE];
int c[N], d[N];

int L[SIZE], R[SIZE];

int v[SIZE];
int u[SIZE];

struct polynomial
{
    int m;
    int num[SIZE];

    polynomial()
    {
        m = 0;
        memset(num, 0, sizeof(num));
    }

    polynomial(int a, int b, int c) { m = a, num[0] = b, num[1] = c; }
};

polynomial operator+(polynomial a, polynomial b)
{
    polynomial c;

    c.m = a.m;
    for (int i = 0; i <= a.m; i++)
        c.num[i] = (a.num[i] + b.num[i]) % mod;

    return c;
}

polynomial operator*(polynomial a, polynomial b)
{
    polynomial c;

    c.m = a.m + b.m;
    for (int i = 0; i <= a.m; i++)
        for (int j = 0; j <= b.m; j++)
            c.num[i + j] = ((c.num[i + j] + 1ll * a.num[i] * b.num[j]) % mod + mod) % mod;

    return c;
}

int calc(polynomial a, int x)
{
    int ans = 0;
    for (int i = 0, val = 1; i <= a.m; i++, val = 1ll * val * x % mod)
        ans = (ans + 1ll * a.num[i] * val) % mod;
    return ans;
}

polynomial g[SIZE];

int val[SIZE];

void Lagrange(int K)
{
    val[0] = 0;
    for (int i = 1; i <= K + 2; i++)
        val[i] = (val[i - 1] + power(i, K, mod)) % mod;

    g[K].m = K + 1;

    for (int i = 1; i <= K + 2; i++)
    {
        polynomial p = polynomial(0, 1, 0);
        int q = 1;

        for (int j = 1; j <= K + 2; j++)
        {
            if (i == j)
                continue;
            p = p * polynomial(1, mod - j, 1);
            q = 1ll * q * (((i - j) + mod) % mod) % mod;
        }

        p = p * polynomial(0, power(q, mod - 2, mod), 0);
        p = p * polynomial(0, val[i], 0);

        g[K] = g[K] + p;
    }
}

int ans;

int main()
{
    n = read(), k = read();

    for (int i = 1; i <= k; i++)
        w[i] = read();

    for (int i = 1; i <= n; i++)
        c[i] = read(), d[i] = read();

    // judgment has no answer.

    for (int i = 1; i <= k; i++)
        L[i] = 1, R[i] = w[i];

    for (int i = 1; i <= n; i++)
    {
        v[c[i]] += d[i];

        if (v[c[i]])
        {
            if (v[c[i]] > 0)
            {
                int val = v[c[i]];
                if (w[c[i]] - val < R[c[i]])
                    R[c[i]] = w[c[i]] - val;
            }
            else
            {
                int val = -v[c[i]];
                if (val + 1 > L[c[i]])
                    L[c[i]] = val + 1;
            }
        }
    }

    bool flag1 = 1;
    for (int i = 1; i <= k; i++)
        if (L[i] > R[i])
            flag1 = 0;

    bool flag2 = 1;
    for (int i = 1; i <= k; i++)
        if (v[i])
            flag2 = 0;

    if (flag1 && flag2)
    {
        puts("-1");
        return 0;
    }

    // work

    for (int i = 1; i <= k; i++)
        L[i] = 1, R[i] = w[i];

    for (int i = 1; i <= n; i++)
    {
        int C = c[i], D = d[i];

        u[C] += D;

        bool great = 0;

        if (u[C])
        {
            if (u[C] > 0)
            {
                int val = u[C];
                if (w[C] - val < R[C])
                    R[C] = w[C] - val, great = 1;
            }
            else
            {
                int val = -u[C];
                if (val + 1 > L[C])
                    L[C] = val + 1, great = 1;
            }
        }

        if (great)
        {
            int val = 1;
            for (int j = 1; j <= k; j++)
            {
                if (j == C)
                    continue;
                val = 1ll * val * (R[j] - L[j] + 1) % mod;
            }

            ans = (ans + 1ll * val * i) % mod;

            if (L[C] > R[C])
            {
                printf("%d\n", ans);
                return 0;
            }
        }
    }

    for (int i = 0; i <= k; i++)
        Lagrange(i);

    for (int i = n + 1; i <= 2 * n; i++)
    {
        int C = c[i - n], D = d[i - n];

        u[C] += D;

        bool great = 0;

        if (u[C])
        {
            if (u[C] > 0)
            {
                int val = u[C];
                if (w[C] - val < R[C])
                    great = 1;
            }
            else
            {
                int val = -u[C];
                if (val + 1 > L[C])
                    great = 1;
            }
        }

        if (great)
        {
            int Round = 0x3f3f3f3f;

            for (int j = 1; j <= k; j++)
            {
                if (!v[j])
                    continue;
                Round = min(Round, ((R[j] - L[j]) / abs(v[j])) + 1);
            }

            polynomial f = polynomial(0, 1, 0);

            f = f * polynomial(1, i - n, n);

            for (int j = 1; j <= k; j++)
            {
                if (j == C)
                    continue;
                f = f * polynomial(1, R[j] - L[j] + 1 + abs(v[j]), mod - abs(v[j]));
            }

            for (int j = 0; j <= k; j++)
                ans = (ans + 1ll * f.num[j] * calc(g[j], Round)) % mod;
        }

        if (u[C])
        {
            if (u[C] > 0)
            {
                int val = u[C];
                if (w[C] - val < R[C])
                    R[C] = w[C] - val;
            }
            else
            {
                int val = -u[C];
                if (val + 1 > L[C])
                    L[C] = val + 1;
            }
        }

        if (L[C] > R[C])
        {
            printf("%d\n", ans);
            return 0;
        }
    }

    printf("%d\n", ans);

    return 0;
}