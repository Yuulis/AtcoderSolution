#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

constexpr int INF = 1e+9;

using Pair_int = pair<int, int>;

// ======================================== //

Pair_int op(Pair_int a, Pair_int b)
{
    return { min(a.first, b.first), max(a.second, b.second) };
}

Pair_int e() { return { INF, -INF }; }

Pair_int f(int x) {
    if (x == -1) {
        return { INF, -INF };
    }
    else {
        return { x, x };
    }
}

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<Pair_int> A(N);
    rep(i, 0, N) {
        int a;
        cin >> a;
        A[i] = f(a);
    }

    segtree<Pair_int, op, e> seg(A);

    while (Q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int i, x;
            cin >> i >> x;
            seg.set(i - 1, f(x));
        }
        else if (t == 2) {
            int l, r;
            cin >> l >> r;

            auto [mi, mx] = seg.prod(l - 1, r);

            if (mi == mx || mi == INF) {
                cout << "Yes" << endl;
            }
            else {
                cout << "No" << endl;
            }
        }
    }

    return 0;
}