#include <bits/stdc++.h>

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using namespace std;
using ll = long long;

// ======================================== //

int main()
{
    ll N, L;
    cin >> N >> L;
    vector<int> d(N - 1);
    rep(i, 0, N - 1) cin >> d[i];

    if (L % 3 != 0)
    {
        cout << 0 << endl;
        return 0;
    }

    vector<ll> pos(N, 0);
    map<ll, ll> cnt;
    cnt[0]++;
    rep(i, 1, N)
    {
        pos[i] = (pos[i - 1] + d[i - 1]) % L;
        cnt[pos[i]]++;
    }

    ll ans = 0;
    ll distance = L / 3;
    rep(i, 0, distance)
    {
        ans += cnt[i] * cnt[i + distance] * cnt[i + 2 * distance];
    }

    cout << ans << endl;

    return 0;
}
