#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// ======================================== //

ll solve() {
    ll X, Y, K;
    cin >> X >> Y >> K;

    ll ans = 0;
    while (X != Y) {
        if (X > Y) X /= K;
        else Y /= K;

        ans++;
    }

    return ans;
}

int main()
{
    int T;
    cin >> T;

    while (T--) {
        cout << solve() << endl;
    }

    return 0;
}