#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int H, W, K;
    cin >> H >> W >> K;
    vector<string> S(H);
    rep(i, 0, H) cin >> S[i];

    vector<vector<int>> grid(H, vector<int>(W, -1));
    rep(i, 0, H) rep(j, 0, W) grid[i][j] = S[i][j] - '0';

    ll ans = 0;
    rep(top, 0, H) {
        vector<int> col_sum(W, 0);
        rep(bottom, top, H) {
            rep(j, 0, W) col_sum[j] += grid[bottom][j];

            auto count = [&](int x) -> ll {
                if (x == 0) return W * (W + 1) / 2;

                ll res = 0;
                int r = 0, sum = 0;
                rep(l, 0, W) {
                    while (r < W && sum < x) {
                        sum += col_sum[r];
                        r++;
                    }

                    if (sum >= x) res += W - r + 1;
                    sum -= col_sum[l];
                }

                return res;
                };

            ans += count(K) - count(K + 1);
        }
    }


    cout << ans << endl;

    return 0;
}