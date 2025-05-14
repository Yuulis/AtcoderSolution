#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    ll sum = 0, sq_sum = 0;
    rep(i, 0, N)
    {
        sum += A[i];
        sq_sum += A[i] * A[i];
    }

    ll ans = (sum * sum - sq_sum) / 2;

    cout << ans << endl;

    return 0;
}