#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N, Q;
    cin >> N >> Q;

    fenwick_tree<ll> row(Q + 1), col(Q + 1);
    vector<int> row_time(N + 1, 0), col_time(N + 1, 0);

    row.add(0, N);
    col.add(0, N);

    ll ans = 0;
    int time = 0;
    while (Q--)
    {
        int t;
        cin >> t;
        time++;

        if (t == 1) {
            int R;
            cin >> R;

            ans += col.sum(0, time) - col.sum(0, row_time[R]);
            row.add(row_time[R], -1);
            row_time[R] = time;
            row.add(row_time[R], 1);
        }
        else {
            int C;
            cin >> C;

            ans -= (N - row.sum(0, col_time[C] + 1));
            col.add(col_time[C], -1);
            col_time[C] = time;
            col.add(col_time[C], 1);
        }

        cout << ans << endl;
    }

    return 0;
}