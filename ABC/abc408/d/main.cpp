#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

constexpr int INF = 1e+9;

template <typename T>
inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false)); }

// ======================================== //

int solve()
{
    int N;
    string S;
    cin >> N >> S;

    vector<vector<int>> dp(N + 1, vector<int>(3, INF));
    dp[0][0] = 0;

    rep(i, 0, N)
    {
        if (S[i] == '0')
        {
            chmin(dp[i + 1][0], dp[i][0] + 0);
            chmin(dp[i + 1][1], dp[i][0] + 1);
            chmin(dp[i + 1][1], dp[i][1] + 1);
            chmin(dp[i + 1][2], dp[i][1] + 0);
            chmin(dp[i + 1][2], dp[i][2] + 0);
        }
        else
        {
            chmin(dp[i + 1][0], dp[i][0] + 1);
            chmin(dp[i + 1][1], dp[i][0] + 0);
            chmin(dp[i + 1][1], dp[i][1] + 0);
            chmin(dp[i + 1][2], dp[i][1] + 1);
            chmin(dp[i + 1][2], dp[i][2] + 1);
        }
    }

    return min({dp[N][0], dp[N][1], dp[N][2]});
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