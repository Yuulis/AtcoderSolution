#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    vector<ll> S(N + 1, 0), T(N + 1, 0), C(N + 1, 0);
    rep(i, 0, N)
    {
        S[i + 1] = S[i] + A[i];
        T[i + 1] = T[i] + S[i + 1];
        C[i + 1] = C[i] + (i + 1);
    }

    auto f = [&](ll x) -> ll {
        if (x == 0) return 0;

        int k = lower_bound(all(C), x) - C.begin();
        return T[k - 1] + S[x - C[k - 1]];
        };

    while (Q--)
    {
        ll L, R;
        cin >> L >> R;

        cout << f(R) - f(L - 1) << endl;
    }

    return 0;
}