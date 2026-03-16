#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

using mint = static_modint<10007>;
using mintM = dynamic_modint<1>;
using mint9M = dynamic_modint<2>;

int main()
{
    ll K, M;
    cin >> K >> M;
    vector<ll> c(K), l(K);
    rep(i, 0, K) cin >> c[i] >> l[i];
    mintM::set_mod(M);
    mint9M::set_mod(9 * M);

    mint N_mint = 0;
    mintM R = 0;
    rep(i, 0, K)
    {
        N_mint = N_mint * mint(10).pow(l[i]) + (c[i] * (mint(10).pow(l[i]) - 1) * mint(9).inv());
        ll r = (mint9M(10).pow(l[i]).val() - 1) / 9;
        R = R * mintM(10).pow(l[i]) + mintM(r) * c[i];
    }

    mint ans = (N_mint - R.val()) * mint(M).inv();
    cout << ans.val() << endl;

    return 0;
}