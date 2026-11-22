#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

constexpr auto PI = 3.14159265358979;
constexpr int INF = 1e+9;

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(M);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, M) cin >> B[i];

    vector<vector<int>> dp(N + 1, vector<int>(M + 1, INF));
    rep(i, 0, N + 1) dp[i][0] = i;
    rep(j, 0, M + 1) dp[0][j] = j;

    rep(i, 1, N + 1) rep(j, 1, M + 1)
    {
        dp[i][j] = min({
            dp[i - 1][j] + 1,
            dp[i][j - 1] + 1,
            dp[i - 1][j - 1] + (A[i - 1] != B[j - 1])
            });
    }

    cout << dp[N][M] << endl;

    return 0;
}