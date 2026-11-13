#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define rrep(i, start, end) for (auto i = (start); (i) >= (end); (i)--)

constexpr long long INFL = 1e+18;

using ll = long long;

template <typename T>
inline bool chmax(T& a, T b) { return ((a < b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    vector<ll> ps(N + 1, 0);
    rep(i, 0, N) ps[i + 1] = ps[i] + A[i];

    vector<ll> pre_mi(N + 1, INFL), pre_mx(N + 1, -INFL);
    pre_mi[0] = pre_mx[0] = 0;
    rep(i, 0, N) {
        pre_mi[i + 1] = min(pre_mi[i], ps[i + 1]);
        pre_mx[i + 1] = max(pre_mx[i], ps[i + 1]);
    }

    vector<ll> suf_mi(N + 1, INFL), suf_mx(N + 1, -INFL);
    suf_mi[N] = suf_mx[N] = ps[N];
    rrep(i, N - 1, 0) {
        suf_mi[i] = min(suf_mi[i + 1], ps[i]);
        suf_mx[i] = max(suf_mx[i + 1], ps[i]);
    }

    ll ans = pre_mx[N] - pre_mi[N] + 1;
    rep(i, 1, N + 1) {
        ll l = min(pre_mi[i - 1], suf_mi[i] - 2 * A[i - 1]);
        ll r = max(pre_mx[i - 1], suf_mx[i] - 2 * A[i - 1]);
        chmax(ans, r - l + 1);
    }

    cout << ans << endl;

    return 0;
}