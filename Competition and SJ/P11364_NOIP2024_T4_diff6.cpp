#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <stack>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <numeric>
#include <cassert>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>
#include <random>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <regex>
#include <iterator>
#include <utility>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <tuple>
#include <optional>
#include <variant>
#include <any>
#include <new>
#include <scoped_allocator>
#include <memory_resource>
#include <cstddef>
#include <cstdlib>
#include <csignal>
#include <csetjmp>
#include <cstdarg>
#include <cstdbool>
#include <ciso646>
#include <cctype>
#include <cwctype>
#include <cstring>
#include <cwchar>
#include <cuchar>
#include <cstdlib>
#include <cstddef>
#include <climits>
#include <cfloat>
#include <cstdint>
#include <cinttypes>
#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <system_error>
#include <cerrno>
#include <cctype>
#include <cwctype>
#include <cstring>
#include <cwchar>
#include <cuchar>
#define pb push_back
#define inf 0x3f3f3f3f
#define ll long long
#define cmax(a, b) a = max(a, b)
#define cmin(a, b) a = min(a, b)
#define rst(a, x) memset(a, x, sizeof(a))
#define ls p << 1
#define rs p << 1 | 1
#define lowbit(x) ((x) & -(x))
#define FAST                     \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);            \
    cout.tie(nullptr);
#define file(filename)                   \
    FAST;                                \
    freopen(filename ".in", "r", stdin); \
    freopen(filename ".out", "w", stdout);
#define Test(filename, number)                  \
    FAST;                                       \
    freopen(filename number ".in", "r", stdin); \
    freopen(filename ".out", "w", stdout);

using namespace std;

const int N(5e5 + 5);

struct segment_tree
{
    int t[N << 2];
    void build(int l, int r, int p)
    {
        t[p] = 0;
        if (l == r)
            return;
        int mid = l + r >> 1;
        build(l, mid, ls);
        build(mid + 1, r, rs);
    }
    void update(int l, int r, int p, int x, int v)
    {
        if (l == r)
            return cmax(t[p], v), void();
        int mid = l + r >> 1;
        if (x <= mid)
            update(l, mid, ls, x, v);
        else
            update(mid + 1, r, rs, x, v);
        t[p] = max(t[ls], t[rs]);
    }
    int query(int l, int r, int p, int L, int R)
    {
        if (L <= l && r <= R)
            return t[p];
        int mid = l + r >> 1, res = 0;
        if (L <= mid)
            res = query(l, mid, ls, L, R);
        if (R > mid)
            cmax(res, query(mid + 1, r, rs, L, R));
        return res;
    }
} T;

int n, m, q, dep[N], ans[N];
struct node
{
    int l, r, v, id;
} a[N << 1], b[N];
vector<int> G[N];
map<int, int> mp[N];

void dfs(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    a[++m] = {u, u, dep[u], 1};
    mp[u][u] = u;
    for (int v : G[u])
    {
        if (v == fa)
            continue;
        dfs(v, u);
        if (mp[v].size() > mp[u].size())
            swap(mp[u], mp[v]);
        for (auto x : mp[v])
        {
            int l = x.first, r = x.second;
            bool flag = 0;
            auto it = mp[u].upper_bound(r);
            if (it != mp[u].end() && it->first == r + 1)
            {
                r = it->second;
                mp[u].erase(it);
                flag = 1;
            }
            it = mp[u].upper_bound(r);
            if (it != mp[u].begin())
            {
                it--;
                if (it->second == l - 1)
                {
                    l = it->first;
                    mp[u].erase(it);
                    flag = 1;
                }
            }
            mp[u][l] = r;
            if (flag)
                a[++m] = {l, r, dep[u], r - l + 1};
        }
    }
}

void solve()
{
    T.build(1, n, 1);
    sort(a + 1, a + m + 1, [&](node x, node y)
         { return x.l < y.l; });
    sort(b + 1, b + q + 1, [&](node x, node y)
         { return x.l < y.l; });
    for (int i = 1, j = 1; i <= q; i++)
    {
        while (j <= m && a[j].l <= b[i].l)
        {
            T.update(1, n, 1, a[j].r, a[j].v);
            j++;
        }
        cmax(ans[b[i].id], T.query(1, n, 1, b[i].l + b[i].v - 1, n));
    }
}

int main()
{
    FAST
            cin >>
        n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0);
    cin >> q;
    for (int i = 1; i <= q; i++)
    {
        cin >> b[i].l >> b[i].r >> b[i].v;
        b[i].id = i;
    }
    sort(a + 1, a + m + 1, [&](node x, node y)
         { return x.id > y.id; });
    sort(b + 1, b + q + 1, [&](node x, node y)
         { return x.v > y.v; });
    for (int i = 1, j = 1; i <= q; i++)
    {
        while (j <= m && a[j].id >= b[i].v)
        {
            T.update(1, n, 1, a[j].l, a[j].v);
            j++;
        }
        ans[b[i].id] = T.query(1, n, 1, b[i].l, b[i].r - b[i].v + 1);
    }
    solve();
    for (int i = 1; i <= q; i++)
    {
        cout << ans[i] << '\n';
    }
    return 0;
}