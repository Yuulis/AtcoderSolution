#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;
using Pair_ll = pair<ll, ll>;

template <typename T>
inline bool chmax(T& a, T b) { return ((a < b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N, K, M;
    cin >> N >> K >> M;
    vector<Pair_ll> jewels(N);
    rep(i, 0, N) cin >> jewels[i].first >> jewels[i].second;

    sort(all(jewels), [](auto& a, auto& b) {
        if (a.second == b.second)
            return a.first > b.first;
        return a.second > b.second;
        });

    vector<int> cnt(N, 0);
    vector<ll> remove_cands;

    ll ans = 0;
    int kinds = 0;
    rep(i, 0, K) {
        auto [c, v] = jewels[i];
        c--;

        ans += v;

        if (cnt[c] == 0) {
            kinds++;
        }
        else {
            remove_cands.push_back(v);
        }

        cnt[c]++;
    }

    if (kinds >= M) {
        cout << ans << endl;
        return 0;
    }

    vector<ll> best_add(N, -1);
    rep(i, K, N) {
        auto [c, v] = jewels[i];
        c--;

        if (cnt[c] == 0)
            chmax(best_add[c], v);
    }

    vector<ll> add_cands;
    rep(c, 0, N) {
        if (best_add[c] != -1) {
            add_cands.push_back(best_add[c]);
        }
    }

    sort(rall(add_cands));
    sort(all(remove_cands));

    rep(i, 0, M - kinds) {
        ans += add_cands[i];
        ans -= remove_cands[i];
    }

    cout << ans << endl;

    return 0;
}
