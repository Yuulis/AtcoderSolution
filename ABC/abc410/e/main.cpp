#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define repe(i, start, end) for (auto i = (start); (i) <= (end); (i)++)

constexpr int INF = 1e+9;

// ======================================== //

int main()
{
    int N, H, M;
    cin >> N >> H >> M;
    vector<int> A(N), B(N);
    rep(i, 0, N) cin >> A[i] >> B[i];

    vector<vector<int>> dp(N + 1, vector<int>(H + 1, INF));
    dp[0][0] = 0;
    int ans = 0;

    repe(i, 1, N)
    {
        repe(h, 0, H)
        {
            int cost_1 = (h >= A[i - 1]) ? dp[i - 1][h - A[i - 1]] : INF;
            int cost_2 = (dp[i - 1][h] != INF) ? dp[i - 1][h] + B[i - 1] : INF;

            dp[i][h] = min(cost_1, cost_2);

            if (dp[i][h] > M)
                dp[i][h] = INF;
        }

        bool flag = false;
        repe(h, 0, H)
        {
            if (dp[i][h] != INF)
                flag = true;
        }

        if (flag)
            ans++;
        else
            break;
    }

    cout << ans << endl;

    return 0;
}