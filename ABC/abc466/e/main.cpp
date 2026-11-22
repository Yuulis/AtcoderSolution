#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

constexpr long long INFL = 1e+18;

using ll = long long;

template <typename T>
inline bool chmax(T& a, T b) { return ((a < b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N, K;
    cin >> N >> K;
    vector<ll> A(N), B(N);
    ll ans = 0;
    rep(i, 0, N) cin >> A[i] >> B[i], ans += A[i];

    vector<ll>  dp0(K + 1, -INFL), dp1(K + 1, -INFL);
    dp0[0] = 0;
    rep(i, 0, N) {
        ll diff = B[i] - A[i];

        vector<ll> ndp0(K + 1, -INFL), ndp1(K + 1, -INFL);
        rep(j, 0, K + 1) {
            ndp0[j] = max(dp0[j], dp1[j]);

            if (j >= 1) {
                ndp1[j] = max(dp0[j - 1], dp1[j]) + diff;
            }
        }

        swap(ndp0, dp0);
        swap(ndp1, dp1);
    }

    ll add = 0;
    rep(i, 0, K + 1) chmax(add, max(dp0[i], dp1[i]));

    cout << ans + add << endl;

    return 0;
}