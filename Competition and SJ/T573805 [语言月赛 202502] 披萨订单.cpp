#include <iostream>
#include <vector>
#define ll long long
using namespace std;

int main()
{
    ll X, Y, K;
    cin >> X >> Y >> K;

    ll max_ = 0;
    ll cnt = 0;

    for (ll b = 0; b <= X; ++b)
    {
        for (ll p = 1; p <= Y; ++p)
        {
            for (ll z = 0; z <= K; ++z)
            {
                ll t = (b + p) ^ z;
                if (t > max_)
                {
                    max_ = t;
                    cnt = 1;
                }
                else if (t == max_)
                {
                    ++cnt;
                }
            }
        }
    }

    cout << max_ << endl;
    cout << cnt << endl;

    return 0;
}