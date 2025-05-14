#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

constexpr int INF = 1e+9;

using Pair_int = pair<int, int>;

// ======================================== //

int di[4] = {1, 0, -1, 0};
int dj[4] = {0, 1, 0, -1};

int main()
{
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    rep(i, 0, H) cin >> S[i];

    vector<vector<int>> dist(H, vector<int>(W, INF));
    queue<Pair_int> que;
    rep(i, 0, H) rep(j, 0, W)
    {
        if (S[i][j] == 'E')
        {
            dist[i][j] = 0;
            que.push({i, j});
        }
    }

    while (!que.empty())
    {
        auto [ci, cj] = que.front();
        que.pop();
        rep(dir, 0, 4)
        {
            int ni = ci + di[dir];
            int nj = cj + dj[dir];
            if (ni < 0 || ni >= H || nj < 0 || nj >= W)
                continue;

            if (S[ni][nj] == '#')
                continue;

            if (dist[ni][nj] > dist[ci][cj] + 1)
            {
                dist[ni][nj] = dist[ci][cj] + 1;
                que.push({ni, nj});
            }
        }
    }

    vector<string> T = S;
    rep(i, 0, H) rep(j, 0, W)
    {
        if (S[i][j] == '.')
        {
            rep(dir, 0, 4)
            {
                int ni = i + di[dir];
                int nj = j + dj[dir];
                if (ni < 0 || ni >= H || nj < 0 || nj >= W)
                    continue;

                if (S[ni][nj] == '#')
                    continue;

                if (dist[ni][nj] == dist[i][j] - 1)
                {
                    char c;
                    if (dir == 0)
                        c = 'v';
                    else if (dir == 1)
                        c = '>';
                    else if (dir == 2)
                        c = '^';
                    else
                        c = '<';

                    T[i][j] = c;
                    break;
                }
            }
        }
    }

    rep(i, 0, H) cout << T[i] << endl;

    return 0;
}