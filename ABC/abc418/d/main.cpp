#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N;
    string T;
    cin >> N >> T;

    vector<vector<int>> dp(N + 1, vector<int>(2, 0));
    rep(j, 0, N)
    {
        if (T[j] == '0')
        {
            dp[j + 1][0] = dp[j][1];
            dp[j + 1][1] = dp[j][0] + 1;
        }
        else
        {
            dp[j + 1][0] = dp[j][0] + 1;
            dp[j + 1][1] = dp[j][1];
        }
    }

    ll ans = 0;
    rep(j, 0, N + 1)
    {
        ans += dp[j][0];
    }

    cout << ans << endl;

    return 0;
}