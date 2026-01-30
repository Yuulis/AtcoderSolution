#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define rrep(i, start, end) for (auto i = (start); (i) >= (end); (i)--)

constexpr int INF = 1e+9;

// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<string> S(N);
    rep(i, 0, N) cin >> S[i];

    vector<int> dp(N + 1, 0);
    rep(i, 0, N)
    {
        vector<int> blacks(N + 1, 0);
        rep(j, 0, N) blacks[j + 1] = blacks[j] + (S[i][j] == '#');

        auto calc_cost = [&](int k) -> int
        {
            int to_white = blacks[k];
            int to_black = (N - blacks[N]) - (k - blacks[k]);
            return to_white + to_black;
        };

        vector<int> ps_min(N + 2, INF);
        rrep(k, N, 0) ps_min[k] = min(ps_min[k + 1], dp[k]);

        rep(k, 0, N + 1) dp[k] = calc_cost(k) + ps_min[k];
    }

    cout << *min_element(all(dp)) << endl;

    return 0;
}