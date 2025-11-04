#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define repe(i, start, end) for (auto i = (start); (i) <= (end); (i)++)

using ll = long long;

ll floor_sqrt(ll x)
{
    ll y = sqrt(x);
    while (y * y > x)
        y--;
    while ((y + 1) * (y + 1) <= x)
        y++;
    return y;
}

// ======================================== //

int main()
{
    int T;
    cin >> T;

    vector<ll> pow10(11, 1);
    rep(i, 1, 11) pow10[i] = pow10[i - 1] * 10;

    auto solve = [&]() -> ll
    {
        ll C, D;
        cin >> C >> D;

        ll ans = 0;
        repe(k, 1, 10)
        {
            ll l_x = max<ll>(1, pow10[k - 1] - C);
            ll r_x = min<ll>(D, pow10[k] - 1 - C);
            if (l_x > r_x)
                continue;

            ll l_val = pow10[k] * C + C + l_x;
            ll r_val = pow10[k] * C + C + r_x;

            ans += floor_sqrt(r_val) - floor_sqrt(l_val - 1);
        }

        return ans;
    };

    while (T--)
    {
        cout << solve() << endl;
    }

    return 0;
}