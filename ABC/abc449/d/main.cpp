#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;
using Pair_ll = pair<ll, ll>;

// ======================================== //

ll f(ll x, ll y)
{
    if (y < x)
        swap(x, y);

    ll res = 0;
    if (x % 2 == 0)
        res += (x + 1) * (x + 2) / 2;
    else
        res += x * (x + 1) / 2;

    res += (y / 2 - x / 2) * (x + 1);
    return res;
}

int main()
{
    ll L, R, D, U;
    cin >> L >> R >> D >> U;

    auto calc = [](ll l, ll r, ll d, ll u) -> ll
    {
        return f(r, u) - f(l - 1, u) - f(r, d - 1) + f(l - 1, d - 1);
    };

    auto convert_interval = [](ll l, ll r) -> vector<Pair_ll>
    {
        vector<Pair_ll> res;
        if (r >= 0)
            res.push_back({max(0LL, l), r});
        if (l < 0)
            res.push_back({max(1LL, -r), -l});

        return res;
    };

    vector<Pair_ll> lr = convert_interval(L, R);
    vector<Pair_ll> du = convert_interval(D, U);

    ll ans = 0;
    for (auto &&[l, r] : lr)
    {
        for (auto &&[d, u] : du)
        {
            ans += calc(l, r, d, u);
        }
    }

    cout << ans << endl;

    return 0;
}