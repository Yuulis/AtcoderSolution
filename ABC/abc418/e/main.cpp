#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;
using Pair_ll = pair<ll, ll>;

ll gcd(ll x, ll y)
{
    if (x < y)
        swap(x, y);
    ll r;
    while (y > 0)
    {
        r = x % y;
        x = y;
        y = r;
    }
    return x;
}

// ======================================== //

Pair_ll calc_slope(ll dx, ll dy)
{
    if (dx == 0)
        return {1, 0};
    if (dy == 0)
        return {0, 1};

    ll g = gcd(abs(dy), abs(dx));
    dy /= g;
    dx /= g;
    if (dy < 0)
    {
        dy = -dy;
        dx = -dx;
    }

    return {dy, dx};
}

int main()
{
    int N;
    cin >> N;
    vector<ll> X(N), Y(N);
    rep(i, 0, N) cin >> X[i] >> Y[i];

    map<Pair_ll, int> slopes;
    rep(i, 0, N) rep(j, i + 1, N)
    {
        ll dx = X[j] - X[i];
        ll dy = Y[j] - Y[i];
        slopes[calc_slope(dx, dy)]++;
    }

    ll trapezium_count = 0;
    for (auto [key, value] : slopes)
    {
        trapezium_count += (ll)value * (value - 1) / 2;
    }

    map<Pair_ll, int> mid_poses;
    rep(i, 0, N) rep(j, i + 1, N)
    {
        Pair_ll mid = {X[i] + X[j], Y[i] + Y[j]};
        mid_poses[mid]++;
    }

    ll parallelogram_count = 0;
    for (auto [key, value] : mid_poses)
    {
        parallelogram_count += (ll)value * (value - 1) / 2;
    }

    cout << trapezium_count - parallelogram_count << endl;

    return 0;
}