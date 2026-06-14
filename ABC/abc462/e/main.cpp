#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// ======================================== //

ll solve() {
    ll A, B, X, Y;
    cin >> A >> B >> X >> Y;

    ll x = abs(X), y = abs(Y);

    ll diagonal = 2 * min(A, B);
    ll axis = min(A + B, 4 * min(A, B));

    ll cost = diagonal * min(x, y) + axis * (abs(x - y) / 2);
    if (abs(x - y) % 2 == 1) {
        if (x > y) cost += min(A, 3 * B);
        else if (x < y) cost += min(3 * A, B);
    }

    return cost;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        cout << solve() << endl;
    }

    return 0;
}