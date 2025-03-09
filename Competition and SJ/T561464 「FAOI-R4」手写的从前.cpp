#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

long long np2(long long n)
{
    if (n <= 0)
        return 1;
    long long t = 1;
    while (t < n)
        t <<= 1;
    return t;
}

bool ip2(int n)
{
    return (n & (n - 1)) == 0;
}

void s()
{
    long long m;
    cin >> m;
    vector<long long> b;
    for (int i = 0; (1LL << i) <= m; ++i)
    {
        if (m & (1LL << i))
            b.push_back(1LL << i);
    }
    int k = b.size();
    if (ip2(k))
    {
        sort(b.begin(), b.end());
        for (auto n : b)
            cout << n << " ";
        cout << "\n";
        return;
    }
    int t = np2(k);
    int q = t - k;
    unordered_map<long long, int> c;
    for (auto x : b)
        c[x]++;
    priority_queue<long long, vector<long long>, greater<long long> > pq;
    unordered_set<long long> in_pq;
    for (auto x : b)
    {
        if (x >= 2)
        {
            pq.push(x);
            in_pq.insert(x);
        }
    }
    while (q > 0)
    {
        if (pq.empty())
            break;
        long long x = pq.top();
        pq.pop();
        in_pq.erase(x);
        if (c.find(x) == c.end() || c[x] == 0 || x < 2)
            continue;
        c[x]--;
        if (c[x] == 0)
            c.erase(x);
        long long y = x / 2;
        c[y] += 2;
        q--;
        if (y >= 2 && in_pq.find(y) == in_pq.end())
        {
            pq.push(y);
            in_pq.insert(y);
        }
        if (c.find(x) != c.end() && c[x] > 0 && x >= 2 && in_pq.find(x) == in_pq.end())
        {
            pq.push(x);
            in_pq.insert(x);
        }
    }
    vector<long long> r;
    for (auto &[v, cnt] : c)
    {
        for (int i = 0; i < cnt; ++i)
            r.push_back(v);
    }
    sort(r.begin(), r.end());
    for (auto n : r)
        cout << n << " ";
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        s();
    }
    return 0;
}