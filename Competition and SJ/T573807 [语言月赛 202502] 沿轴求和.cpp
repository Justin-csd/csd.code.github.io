#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    int n, x;
    cin >> n >> x;
    vector<int> d(n);
    int t = 1;
    for (int i = 0; i < n; ++i)
    {
        cin >> d[i];
        t *= d[i];
    }
    map<vector<int>, int> a;
    for (int i = 0; i < t; ++i)
    {
        vector<int> idx(n);
        for (int j = 0; j < n; ++j)
        {
            cin >> idx[j];
        }
        int v;
        cin >> v;
        a[idx] = v;
    }

    map<vector<int>, int> res;
    for (const auto &p : a)
    {
        const vector<int> &idx = p.first;
        int v = p.second;
        vector<int> nidx;
        for (int i = 0; i < n; ++i)
        {
            if (i != x)
                nidx.push_back(idx[i]);
        }
        res[nidx] += v;
    }

    for (const auto &p : res)
    {
        const vector<int> &idx = p.first;
        int sum = p.second;
        for (int i = 0; i < idx.size(); ++i)
        {
            cout << idx[i] << (i == idx.size() - 1 ? "" : " ");
        }
        cout << " " << sum << endl;
    }

    return 0;
}