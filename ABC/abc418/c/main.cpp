#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

template <typename T>
inline bool chmax(T &a, T b) { return ((a < b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    int maxA = 0;
    rep(i, 0, N) cin >> A[i], chmax(maxA, A[i]);

    sort(all(A));

    vector<ll> ps(N + 1);
    rep(i, 0, N) ps[i + 1] = ps[i] + A[i];

    auto solve = [&](ll B) -> ll
    {
        if (maxA < B)
        {
            return -1;
        }

        auto idx = upper_bound(all(A), B - 1) - A.begin();
        ll x = ps[idx] + (B - 1) * (N - idx) + 1;

        return x;
    };

    while (Q--)
    {
        ll B;
        cin >> B;
        cout << solve(B) << endl;
    }

    return 0;
}