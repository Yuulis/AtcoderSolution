#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// ======================================== //

struct Point {
    ll x, y;
};

ll dot_product(Point A, Point B)
{
    return A.x * B.x + A.y * B.y;
}

ll cross_product(Point A, Point B)
{
    return A.x * B.y - A.y * B.x;
}

bool solve() {
    Point P, Q, R, S;
    cin >> P.x >> P.y >> Q.x >> Q.y >> R.x >> R.y >> S.x >> S.y;

    ll ax = Q.x - P.x;
    ll ay = Q.y - P.y;
    ll bx = S.x - R.x;
    ll by = S.y - R.y;

    if (cross_product({ ax, ay }, { bx, by }) != 0) {
        return true;
    }

    ll dx = (R.x + S.x) - (P.x + Q.x);
    ll dy = (R.y + S.y) - (P.y + Q.y);
    if (dot_product({ ax, ay }, { dx, dy }) == 0) {
        return true;
    }
    else {
        return false;
    }
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