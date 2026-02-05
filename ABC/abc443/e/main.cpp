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

    vector<int> status(N, -1);
    status[C - 1] = 1;

    rrep(i, N - 1, 1)
    {
        vector<int> next_status(N, -1);
        bool is_reachable = false;

        rep(j, 0, N)
        {
            if (status[j] == -1)
                continue;

            int current_status = -1;

            repe(dj, -1, 1)
            {
                int ni = i - 1;
                int nj = j + dj;
                if (nj < 0 || nj >= N)
                    continue;

                if (S[ni][nj] == '.')
                {
                    if (lowest_wall[nj] < i)
                        current_status = 1;
                    else if (nj == j)
                        current_status = status[j];
                    else
                        current_status = 0;
                }
                else
                {
                    if (lowest_wall[nj] < i)
                        current_status = 1;
                    else if (nj == j && status[j] == 1)
                        current_status = 1;
                    else
                        current_status = -1;
                }

                if (current_status != -1)
                {
                    chmax(next_status[nj], current_status);
                    is_reachable = true;
                }
            }
        }

        status = next_status;
        if (!is_reachable)
            break;
    }

    string ans;
    rep(j, 0, N) ans += (status[j] == -1 ? '0' : '1');

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