#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

constexpr int INF = 1e+9;

template <typename T>
inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<int> h(N);
    rep(i, 0, N) cin >> h[i];

    vector<int> dp(N + 1, INF);
    dp[0] = 0;

    rep(i, 0, N)
    {
        chmin(dp[i + 1], dp[i] + abs(h[i + 1] - h[i]));
        chmin(dp[i + 2], dp[i] + abs(h[i + 2] - h[i]));
    }

    cout << dp[N - 1] << endl;

    return 0;
}