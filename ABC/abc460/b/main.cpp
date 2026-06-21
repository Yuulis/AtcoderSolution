#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// ======================================== //

bool solve()
{
    ll X1, Y1, R1, X2, Y2, R2;
    cin >> X1 >> Y1 >> R1 >> X2 >> Y2 >> R2;

    ll d2 = (X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2);
    ll diff2 = (R1 - R2) * (R1 - R2);
    ll sum2 = (R1 + R2) * (R1 + R2);

    if (diff2 <= d2 && d2 <= sum2)
        return true;
    else
        return false;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        cout << (solve() ? "Yes" : "No") << endl;
    }

    return 0;
}