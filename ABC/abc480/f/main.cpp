#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

template <typename T>
inline bool chmax(T& a, T b) { return ((a < b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<ll> A(N);
    ll S = 0;
    rep(i, 0, N) cin >> A[i], S += A[i];

    ll T = S / M;

    vector<ll> sum((1 << N), 0);
    rep(bit, 0, (1 << N))
    {
        int prev = bit & (bit - 1);
        int i = __builtin_ctz(bit);
        sum[bit] = sum[prev] + A[i];
    }

    vector<int> dp((1 << N), 0);
    rep(bit, 0, (1 << N))
    {
        for (int sub = bit; sub > 0; sub &= (sub - 1))
        {
            int i = __builtin_ctz(sub);
            int prev = bit ^ (1 << i);
            chmax(dp[bit], dp[prev] + (sum[bit] % T == 0));
        }
    }

    cout << M - dp[(1 << N) - 1] << endl;

    return 0;
}