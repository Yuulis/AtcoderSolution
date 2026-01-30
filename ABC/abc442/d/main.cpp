#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

ll op(ll a, ll b)
{
    return a + b;
}

ll e()
{
    return 0LL;
}

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    segtree<ll, op, e> seg(A);

    while (Q--)
    {
        int t;
        cin >> t;

        if (t == 1)
        {
            int x;
            cin >> x;
            x--;

            ll a = seg.get(x);
            ll b = seg.get(x + 1);
            seg.set(x, b);
            seg.set(x + 1, a);
        }
        else if (t == 2)
        {
            int l, r;
            cin >> l >> r;

            cout << seg.prod(l - 1, r) << endl;
        }
    }

    return 0;
}