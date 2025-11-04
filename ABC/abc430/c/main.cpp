#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N, A, B;
    string S;
    cin >> N >> A >> B >> S;

    vector<int> ps_a(N + 1, 0), ps_b(N + 1, 0);
    rep(i, 0, N)
    {
        if (S[i] == 'a')
            ps_a[i + 1] = ps_a[i] + 1;
        else
            ps_a[i + 1] = ps_a[i];

        if (S[i] == 'b')
            ps_b[i + 1] = ps_b[i] + 1;
        else
            ps_b[i + 1] = ps_b[i];
    }

    ll ans = 0;
    rep(l, 0, N)
    {
        auto itr_a = lower_bound(ps_a.begin() + (l + 1), ps_a.end(), ps_a[l] + A);
        auto itr_b = lower_bound(ps_b.begin() + (l + 1), ps_b.end(), ps_b[l] + B);

        int r_a = distance(ps_a.begin(), itr_a) - 1;
        int r_b = (distance(ps_b.begin(), itr_b) - 1) - 1;

        if (r_a <= r_b)
            ans += r_b - r_a + 1;
    }

    cout << ans << endl;

    return 0;
}