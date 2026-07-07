#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using mint = modint998244353;

// ======================================== //

int main()
{
    string N;
    cin >> N;

    int l = N.size();

    vector<vector<vector<vector<vector<mint>>>>> dp(2, vector<vector<vector<vector<mint>>>>(2, vector<vector<vector<mint>>>(3, vector<vector<mint>>(2, vector<mint>((1 << 10), 0)))));
    dp[0][1][0][0][0] = 1;

    rep(i, 0, l) {
        vector<vector<vector<vector<vector<mint>>>>> ndp(2, vector<vector<vector<vector<mint>>>>(2, vector<vector<vector<mint>>>(3, vector<vector<mint>>(2, vector<mint>((1 << 10), 0)))));
        int limit = N[i] - '0';

        rep(smaller, 0, 2) {
            rep(leading, 0, 2) {
                rep(mod, 0, 3) {
                    rep(has3, 0, 2) {
                        rep(bit, 0, (1 << 10)) {
                            mint now = dp[smaller][leading][mod][has3][bit];
                            if (now.val() == 0) continue;

                            int upper = 9;
                            if (!smaller) upper = limit;

                            rep(d, 0, upper + 1) {
                                int next_smaller = smaller;
                                if (!smaller && d < limit) {
                                    next_smaller = 1;
                                }

                                int next_leading = (leading && d == 0);

                                int next_mod = (mod + d) % 3;
                                int next_has3 = has3;
                                int next_bit = bit;

                                if (!next_leading) {
                                    next_bit |= (1 << d);
                                    if (d == 3) {
                                        next_has3 = 1;
                                    }
                                }

                                ndp[next_smaller][next_leading][next_mod][next_has3][next_bit] += now;
                            }
                        }
                    }
                }
            }
        }

        dp = move(ndp);
    }

    mint ans = 0;
    rep(smaller, 0, 2) {
        int leading = 0;

        rep(mod, 0, 3) {
            rep(has3, 0, 2) {
                rep(bit, 0, (1 << 10)) {
                    mint now = dp[smaller][leading][mod][has3][bit];
                    if (now.val() == 0) continue;

                    int cnt = 0;
                    if (mod == 0) cnt++;
                    if (has3) cnt++;
                    if (__builtin_popcount(bit) == 3) cnt++;

                    if (cnt == 1) {
                        ans += now;
                    }
                }
            }
        }
    }

    cout << ans.val() << endl;

    return 0;
}