#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

constexpr int INF = 1e+9;

template <typename T>
inline bool chmax(T& a, T b) { return ((a < b) ? (a = b, true) : (false)); }
template <typename T>
inline bool chmin(T& a, T b) { return ((a > b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int K;
    cin >> K;

    int mi = INF, mx = 0;
    rep(i, 0, K) {
        int A;
        cin >> A;
        chmin(mi, A);
        chmax(mx, A);
    }

    if (mx != 9) cout << -1 << endl;
    else cout << mi << endl;

    return 0;
}