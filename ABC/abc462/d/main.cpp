#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N, D;
    cin >> N >> D;

    vector<int> time(1001000, 0);
    rep(i, 0, N) {
        int S, T;
        cin >> S >> T;

        if (S <= T - D) {
            time[S]++;
            time[T - D + 1]--;
        }
    }

    ll ans = 0, cnt = 0;
    rep(t, 1, 1001000) {
        cnt += time[t];
        ans += cnt * (cnt - 1) / 2;
    }

    cout << ans << endl;

    return 0;
}