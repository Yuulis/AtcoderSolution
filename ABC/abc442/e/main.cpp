#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
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

int main()
{
    auto norm_dir = [&](ll x, ll y) -> Pair_ll
    {
        if (x == 0 && y == 0)
            return {0, 0};
        if (x == 0)
            return {0, y / abs(y)};
        if (y == 0)
            return {x / abs(x), 0};

        ll g = gcd(abs(x), abs(y));
        return {x / g, y / g};
    };

    int N, Q;
    cin >> N >> Q;
    vector<Pair_ll> dirs(N);
    map<Pair_ll, int> dir_counts;
    rep(i, 0, N)
    {
        ll X, Y;
        cin >> X >> Y;
        dirs[i] = norm_dir(X, Y);
        dir_counts[dirs[i]]++;
    }

    vector<Pair_ll> unique_dirs;
    for (auto [dir, count] : dir_counts)
    {
        unique_dirs.push_back(dir);
    }
    sort(all(unique_dirs), [](Pair_ll a, Pair_ll b)
         { return atan2l(a.second, a.first) < atan2l(b.second, b.first); });

    int l = unique_dirs.size();
    vector<ll> ps(l + 1, 0);
    rep(i, 0, l) ps[i + 1] = ps[i] + dir_counts[unique_dirs[i]];

    map<Pair_ll, int> dir_to_idx;
    rep(i, 0, l)
        dir_to_idx[unique_dirs[i]] = i;

    while (Q--)
    {
        int A, B;
        cin >> A >> B;
        A--;
        B--;

        int idx_a = dir_to_idx[dirs[A]];
        int idx_b = dir_to_idx[dirs[B]];
        if (idx_a >= idx_b)
        {
            cout << ps[idx_a + 1] - ps[idx_b] << endl;
        }
        else
        {
            cout << ps[idx_a + 1] + (ps[l] - ps[idx_b]) << endl;
        }
    }

    return 0;
}