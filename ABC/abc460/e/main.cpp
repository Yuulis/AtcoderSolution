#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define repe(i, start, end) for (auto i = (start); (i) <= (end); (i)++)

using ll = long long;
using mint = modint998244353;

// ======================================== //

using i128 = __int128_t;
constexpr int MOD = 998244353;

ll solve() {
    ll N, M;
    cin >> N >> M;

    vector<i128> pow10(20);
    pow10[0] = 1;
    repe(i, 1, 19) {
        pow10[i] = pow10[i - 1] * 10;
    }

    mint ans = 0;

    repe(d, 1, 19) {
        i128 right = min<i128>(N, pow10[d] - 1);
        i128 cnt_y = max<i128>(0, right - pow10[d - 1] + 1);

        if (cnt_y == 0) continue;

        ll r = (pow_mod(10, d, M) - 1 + M) % M;
        ll g = gcd(M, r);

        ll Ld = M / g;
        ll cnt_x = N / Ld;

        ans += mint((ll)(cnt_y % MOD)) * mint(cnt_x % MOD);
    }

    return ans.val();
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