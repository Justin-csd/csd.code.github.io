#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        string a, b, c, d;
        cin >> n >> a >> b >> c >> d;

        vector<int> p(n), q(n), even_a(n + 1, 0), odd_a(n + 1, 0), even_b(n + 1, 0), odd_b(n + 1, 0);
        int ans = 0;

        // Initialize the first element
        p[0] = 0;
        q[0] = 0;
        if (a[0] & 1)
        {
            odd_a[0]++;
        }
        else
        {
            even_a[0]++;
        }
        if (b[0] & 1)
        {
            odd_b[0]++;
        }
        else
        {
            even_b[0]++;
        }

        // Process string c
        for (int i = 1; i < n; ++i)
        {
            p[i] = ((c[i] & 1) && (c[i - 1] & 1)) ? p[i - 1] : i;
            if (a[i] & 1)
            {
                odd_a[p[i]]++;
            }
            else
            {
                even_a[p[i]]++;
            }
        }

        // Process string d
        for (int i = 1; i < n; ++i)
        {
            q[i] = ((d[i] & 1) && (d[i - 1] & 1)) ? q[i - 1] : i;
            if (b[i] & 1)
            {
                odd_b[q[i]]++;
            }
            else
            {
                even_b[q[i]]++;
            }
        }

        // Calculate the answer
        for (int i = 0; i < n; ++i)
        {
            if (even_a[p[i]] && even_b[q[i]])
            {
                ans++;
                even_a[p[i]]--;
                even_b[q[i]]--;
            }
            else if (odd_a[p[i]] && odd_b[q[i]])
            {
                ans++;
                odd_a[p[i]]--;
                odd_b[q[i]]--;
            }
            else if (even_a[p[i]])
            {
                even_a[p[i]]--;
                odd_b[q[i]]--;
            }
            else
            {
                odd_a[p[i]]--;
                even_b[q[i]]--;
            }
        }

        cout << ans << "\n";
    }
    return 0;
}