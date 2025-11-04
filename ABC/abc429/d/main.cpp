#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    ll N, M, C;
    cin >> N >> M >> C;
    map<ll, int> mp;
    rep(i, 0, N)
    {
        ll A;
        cin >> A;
        mp[A]++;
    }

    vector<pair<ll, int>> pos;
    for (auto &[key, val] : mp)
    {
        pos.push_back({key, val});
    }

    int K = pos.size();
    vector<pair<ll, int>> pos2 = pos;
    rep(i, 0, K) pos2.push_back({pos[i].first + M, pos[i].second});

    vector<ll> ps(2 * K + 1, 0);
    rep(i, 0, 2 * K) ps[i + 1] = ps[i] + pos2[i].second;

    auto get_x = [&](int start) -> ll
    {
        ll target_num = ps[start] + C;

        auto it = lower_bound(ps.begin() + start + 1, ps.end(), target_num);
        int target_idx = distance(ps.begin(), it) - 1;

        return ps[target_idx + 1] - ps[start];
    };

    ll ans = 0;
    rep(j, 0, K - 1)
    {
        ll q = pos[j + 1].first - pos[j].first;
        ans += q * get_x(j + 1);
    }

    ll q_end = M - pos[K - 1].first;
    ans += q_end * get_x(K);

    ll q_start = pos[0].first;
    ans += q_start * get_x(0);

    cout << ans << endl;

    return 0;
}