#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define all(x) (x).begin(), (x).end()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N;
    ll L, R;
    cin >> N >> L >> R;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    vector<ll> ps(N + 1, 0);
    rep(i, 0, N) ps[i + 1] = ps[i] + A[i];

    vector<ll> comp_ps = ps;
    sort(all(comp_ps));
    comp_ps.erase(unique(all(comp_ps)), comp_ps.end());

    fenwick_tree<ll> fw(comp_ps.size());
    int p0 = lower_bound(all(comp_ps), ps[0]) - comp_ps.begin();
    fw.add(p0, 1);

    ll ans = 0;
    rep(r, 1, N + 1) {
        int left = lower_bound(all(comp_ps), ps[r] - R) - comp_ps.begin();
        int right = upper_bound(all(comp_ps), ps[r] - L) - comp_ps.begin();
        ans += fw.sum(left, right);

        int p = lower_bound(all(comp_ps), ps[r]) - comp_ps.begin();
        fw.add(p, 1);
    }

    cout << ans << endl;

    return 0;
}