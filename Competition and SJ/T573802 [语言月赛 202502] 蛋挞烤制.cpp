#include <iostream>
using namespace std;

int main()
{
    long long ve, vm, vt;
    long long e, m, t;
    cin >> ve >> vm >> vt;
    cin >> e >> m >> t;

    long long v = ve * e + vm * m;    // 总体积
    long long ts = (v + vt - 1) / vt; // 可烤蛋挞个数
    long long b = (ts + t - 1) / t;   // 最少批数

    cout << b << endl;
    return 0;
}