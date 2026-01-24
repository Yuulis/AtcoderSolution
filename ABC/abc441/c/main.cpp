#include <bits/stdc++.h>
using namespace std;

#define rall(x) (x).rbegin(), (x).rend()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N, K;
    ll X;
    cin >> N >> K >> X;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    sort(rall(A));

    ll ans = -1, sum = 0;
    rep(m, N - K + 1, N + 1)
    {
        sum += A[m - 1];
        if (sum >= X)
        {
            ans = m;
            break;
        }
    }

    cout << ans << endl;

    return 0;
}