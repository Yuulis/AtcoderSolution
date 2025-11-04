#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
constexpr int INF = 1e+9;

template <typename T>
inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N, M, L;
    cin >> N >> M >> L;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];

    vector<vector<int>> cost(L, vector<int>(M, 0));
    rep(i, 0, L) rep(j, 0, M)
    {
        int sum = 0;
        for (int k = i; k < N; k += L)
        {
            sum += (j - A[k] + M) % M;
        }
        cost[i][j] = sum;
    }

    vector<vector<int>> dp(L + 1, vector<int>(M, INF));
    dp[0][0] = 0;
    rep(i, 0, L) rep(j, 0, M) rep(k, 0, M)
    {
        chmin(dp[i + 1][(j + k) % M], dp[i][j] + cost[i][k]);
    }

    cout << dp[L][0] << endl;

    return 0;
}