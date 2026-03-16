#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> C(M);
    rep(i, 0, M) cin >> C[i];
    vector<int> A(N), B(N);
    rep(i, 0, N) cin >> A[i] >> B[i], A[i]--;

    int ans = 0;
    rep(i, 0, N)
    {
        int v = min(B[i], C[A[i]]);
        ans += v;
        C[A[i]] -= v;
    }

    cout << ans << endl;

    return 0;
}