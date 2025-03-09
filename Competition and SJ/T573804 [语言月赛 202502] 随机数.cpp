#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define ll long long
using namespace std;

int main()
{
    ll n, L, R;
    cin >> n >> L >> R;

    vector<ll> seq(n, 0);
    ll sum = 0;

    srand(time(0));

    for (ll i = 0; i < n; ++i)
    {
        seq[i] = rand() % 2000001 - 1000000;
        sum += seq[i];
    }

    ll ta = L + rand() % (R - L + 1);
    ll diff = ta - sum;

    for (ll i = 0; i < n && diff != 0; ++i)
    {
        ll adj = min(max(diff, -1000000 - seq[i]), 1000000 - seq[i]);
        seq[i] += adj;
        diff -= adj;
    }

    for (ll i = 0; i < n; ++i)
    {
        cout << seq[i] << (i == n - 1 ? "\n" : " ");
    }

    return 0;
}