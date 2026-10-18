#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define repe(i, start, end) for (auto i = (start); (i) <= (end); (i)++)

constexpr long long INFL = 1e+18;

using ll = long long;

// ======================================== //

int main()
{
    ll N;
    cin >> N;

    auto check = [&](ll a, ll d, ll l) -> bool {
        ll prod = 1;
        rep(i, 0, l) {
            ll next = a + i * d;
            if (next > N / prod) return false;

            prod *= next;
        }

        return true;
        };

    ll ans = 0;
    repe(l, 3, 20) {
        for (ll a = 1; check(a, 1, l); a++) {
            ll ok = 1, ng = INFL;
            while (ng - ok > 1) {
                ll mid = (ok + ng) / 2;
                if (check(a, mid, l)) ok = mid;
                else ng = mid;
            }

            ans += ok;
        }
    }

    cout << ans << endl;

    return 0;
}