#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define repe(i, start, end) for (auto i = (start); (i) <= (end); (i)++)
#define rrep(i, start, end) for (auto i = (start); (i) >= (end); (i)--)

template <typename T>
inline bool chmax(T &a, T b) { return ((a < b) ? (a = b, true) : (false)); }

// ======================================== //

string solve()
{
    int N, C;
    cin >> N >> C;
    vector<string> S(N);
    rep(i, 0, N) cin >> S[i];

    vector<int> lowest_wall(N, -1);
    rep(j, 0, N) rrep(i, N - 1, 0)
    {
        if (S[i][j] == '#')
        {
            lowest_wall[j] = i;
            break;
        }
    }

    vector<int> dp(N, -1);
    dp[C - 1] = 1;

    rrep(i, N - 2, 0)
    {
        vector<int> next_dp(N, -1);
        bool is_reachable = false;

        rep(j, 0, N)
        {
            repe(dj, -1, 1)
            {
                int pj = j + dj;
                if (pj < 0 || pj >= N)
                    continue;

                if (dp[pj] == -1)
                    continue;

                int current_status = -1;

                if (S[i][j] == '.')
                {
                    if (i > lowest_wall[j])
                        current_status = 1;
                    else if (pj == j)
                        current_status = dp[j];
                    else
                        current_status = 0;
                }
                else
                {
                    if (i == lowest_wall[j])
                        current_status = 1;
                    else if (i < lowest_wall[j])
                    {
                        if (pj == j && dp[pj] == 1)
                            current_status = 1;
                        else
                            current_status = -1;
                    }
                }

                if (current_status != -1)
                {
                    chmax(next_dp[j], current_status);
                    is_reachable = true;
                }
            }
        }

        dp = next_dp;
        if (!is_reachable)
            break;
    }

    string ans;
    rep(j, 0, N) ans += (dp[j] == -1 ? '0' : '1');

    return ans;
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