#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define repe(i, start, end) for (auto i = (start); (i) <= (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N;
    cin >> N;
    map<ll, ll> mp;
    rep(i, 0, N)
    {
        ll A;
        cin >> A;
        mp[A]++;
    }

    ll ans = 0;
    repe(v, 1, N)
    {
        if (mp[v] < 2)
            continue;

        ll pair = mp[v] * (mp[v] - 1) / 2;
        ll other = N - mp[v];
        ans += pair * other;
    }

    cout << ans << endl;

    return 0;
}