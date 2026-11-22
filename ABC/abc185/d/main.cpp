#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

constexpr auto PI = 3.14159265358979;
constexpr int INF = 1e+9;

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
inline bool chmin(T& a, T b) { return ((a > b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(M + 2);
    A[0] = 0, A[M + 1] = N + 1;
    rep(i, 1, M + 1) cin >> A[i];

    sort(all(A));

    vector<int> v;
    int k = INF;
    rep(i, 0, M + 1) {
        int l = A[i + 1] - A[i] - 1;

        if (l > 0) {
            v.push_back(l);
            chmin(k, l);
        }
    }

    int ans = 0;
    for (auto x : v) {
        ans += div_ceil(x, k);
    }

    cout << ans << endl;

    return 0;
}