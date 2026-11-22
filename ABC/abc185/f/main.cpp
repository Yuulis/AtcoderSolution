#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

ll op(ll a, ll b) { return a ^ b; }
ll e() { return 0LL; }

int main()
{
    int N, Q;
    cin >> N >> Q;
    segtree<ll, op, e> A(N);
    rep(i, 0, N) {
        ll a;
        cin >> a;
        A.set(i, a);
    }

    while (Q--)
    {
        int T;
        ll X, Y;
        cin >> T >> X >> Y;

        if (T == 1)
        {
            A.set(X - 1, A.get(X - 1) ^ Y);
        }
        else if (T == 2)
        {
            cout << A.prod(X - 1, Y) << endl;
        }
    }

    return 0;
}