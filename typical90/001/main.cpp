#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N, L, K;
    cin >> N >> L >> K;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];

    auto is_ok = [&](ll x) -> bool
    {
        ll cnt = 0;
        ll last = 0;
        rep(i, 0, N)
        {
            if (A[i] - last >= x)
            {
                cnt++;
                last = A[i];
            }
        }

        if (L - last >= x)
            cnt++;

        return (cnt >= K + 1);
    };

    ll ok = -1, ng = L + 1;
    while (ng - ok > 1)
    {
        ll mid = midpoint(ok, ng);
        if (is_ok(mid))
            ok = mid;
        else
            ng = mid;
    }

    cout << ok << endl;

    return 0;
}