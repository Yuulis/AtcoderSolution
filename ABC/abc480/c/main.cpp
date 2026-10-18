#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

template <class T1, class T2>
inline auto div_ceil(T1 a, T2 b)
{
    if (b < 0)
        a *= -1, b *= -1;
    if (a <= 0)
        return a / b;
    else
        return (a - 1) / b + 1;
}
template <typename T>
inline bool chmax(T& a, T b) { return ((a < b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N;
    ll K, T;
    cin >> N >> K >> T;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    sort(all(A));

    ll right = 0;
    int ans = 0;
    rep(i, 0, N) {
        if (A[i] > T) break;

        if (A[i] > right) {
            ans += div_ceil(A[i] - right, K);
        }

        chmax(right, A[i] + K);
    }

    if (right < T) {
        ans += div_ceil(T - right, K);
    }

    cout << ans << endl;

    return 0;
}