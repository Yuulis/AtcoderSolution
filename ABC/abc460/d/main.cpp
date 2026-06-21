#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
using Pair_int = pair<int, int>;

// ======================================== //

int di[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
int dj[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int main()
{
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    rep(i, 0, H) cin >> S[i];

    vector<Pair_int> B1;
    rep(i, 0, H) rep(j, 0, W) {
        if (S[i][j] == '.') {
            rep(dir, 0, 8) {
                int ni = i + di[dir], nj = j + dj[dir];
                if (0 <= ni && ni < H && 0 <= nj && nj < W && S[ni][nj] == '#') {
                    B1.emplace_back(i, j);
                    break;
                }
            }
        }
    }

    vector<vector<char>> ans(H, vector<char>(W));
    if (B1.empty()) {
        rep(i, 0, H) rep(j, 0, W) ans[i][j] = '.';
    }
    else {

        vector<vector<int>> dist(H, vector<int>(W, -1));
        queue<Pair_int> que;
        for (auto [i, j] : B1) {
            dist[i][j] = 0;
            que.emplace(i, j);
        }

        while (!que.empty()) {
            auto [i, j] = que.front();
            que.pop();

            rep(dir, 0, 8) {
                int ni = i + di[dir], nj = j + dj[dir];
                if (0 <= ni && ni < H && 0 <= nj && nj < W && dist[ni][nj] == -1) {
                    dist[ni][nj] = dist[i][j] + 1;
                    que.emplace(ni, nj);
                }
            }
        }


        rep(i, 0, H) rep(j, 0, W) {
            if (dist[i][j] % 2 == 0) {
                ans[i][j] = '.';
            }
            else {
                ans[i][j] = '#';
            }
        }
    }

    rep(i, 0, H) {
        rep(j, 0, W) cout << ans[i][j];
        cout << endl;
    }

    return 0;
}