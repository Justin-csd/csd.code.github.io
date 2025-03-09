#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    int so = 0;
    for (int ai : a)
    {
        if (ai <= 49)
        {
            so++;
        }
    }

    vector<int> v(n, 0);
    for (int i = 0; i < n; ++i)
    {
        if (a[i] >= 50 && a[i] <= 51)
        {
            v[i] = 1;
        }
    }

    vector<int> psum(n + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        psum[i] = psum[i - 1] + v[i - 1];
    }

    int cnt = 0;
    int req = n / 2;
    for (int l = 0; l <= n - k; ++l)
    {
        int sd = psum[l + k] - psum[l];
        if (so + sd > req)
        {
            cnt++;
        }
    }

    cout << cnt << endl;
    return 0;
}