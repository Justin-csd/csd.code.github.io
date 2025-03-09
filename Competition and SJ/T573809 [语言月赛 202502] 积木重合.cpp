#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    long a1, a2, a3, b1, b2, b3;
    long c1, c2, c3, d1, d2, d3;
    cin >> a1 >> a2 >> a3 >> b1 >> b2 >> b3;
    cin >> c1 >> c2 >> c3 >> d1 >> d2 >> d3;

    long x = max(0L, min(b1, d1) - max(a1, c1) + 1);
    long y = max(0L, min(b2, d2) - max(a2, c2) + 1);
    long z = max(0L, min(b3, d3) - max(a3, c3) + 1);

    long ans = x * y * z;

    cout << ans << endl;

    return 0;
}