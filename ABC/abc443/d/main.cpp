#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define rrep(i, start, end) for (auto i = (start); (i) >= (end); (i)--)

using ll = long long;

template <typename T>
inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false)); }

// ======================================== //

ll solve()
{
    int N;
    cin >> N;
    vector<ll> R(N);
    rep(i, 0, N) cin >> R[i];

    vector<ll> target = R;
    rep(i, 1, N) chmin(target[i], target[i - 1] + 1);
    rrep(i, N - 2, 0) chmin(target[i], target[i + 1] + 1);

    ll ans = 0;
    rep(i, 0, N) ans += R[i] - target[i];

    return ans;
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