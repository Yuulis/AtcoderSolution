#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

constexpr long long INFL = 1e+18;

using ll = long long;

template <class T1, class T2>
inline auto div_ceil(T1 a, T2 b)
{
    if (b < 0)
        a *= -1, b *= -1;
    if (a <= 0)
        return a / b;
    else
        return (a - 1) / b + 1;
}
template <typename T>
inline bool chmax(T &a, T b) { return ((a < b) ? (a = b, true) : (false)); }
template <typename T>
inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N;
    cin >> N;
    ll minR = INFL, maxR = -INFL, minC = INFL, maxC = -INFL;
    rep(i, 0, N)
    {
        ll R, C;
        cin >> R >> C;
        chmin(minR, R);
        chmax(maxR, R);
        chmin(minC, C);
        chmax(maxC, C);
    }

    ll dR = maxR - minR, dC = maxC - minC;

    cout << div_ceil(max(dR, dC), 2LL) << endl;

    return 0;
}