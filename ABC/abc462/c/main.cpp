#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define repe(i, start, end) for (auto i = (start); (i) <= (end); (i)++)

constexpr int INF = 1e+9;

template <typename T>
inline bool chmin(T& a, T b) { return ((a > b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<int> YofX(N + 1);
    rep(i, 0, N) {
        int X, Y;
        cin >> X >> Y;
        YofX[X] = Y;
    }

    int Y_min = INF;
    int ans = 0;
    repe(x, 1, N) {
        int y = YofX[x];

        if (y < Y_min) {
            ans++;
        }

        chmin(Y_min, y);
    }

    cout << ans << endl;

    return 0;
}