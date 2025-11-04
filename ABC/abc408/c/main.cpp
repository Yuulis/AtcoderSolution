#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

constexpr int INF = 1e+9;

template <typename T>
inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> c(N + 2, 0);
    rep(i, 0, M)
    {
        int L, R;
        cin >> L >> R;
        c[L]++;
        c[R + 1]--;
    }

    rep(i, 1, N + 1) c[i] += c[i - 1];

    int ans = INF;
    rep(i, 1, N + 1)
    {
        chmin(ans, c[i]);
    }

    cout << ans << endl;

    return 0;
}