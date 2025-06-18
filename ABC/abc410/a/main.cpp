#include <bits/stdc++.h>

using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, K;
    cin >> N;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];
    cin >> K;

    int ans = 0;
    rep(i, 0, N)
    {
        if (K <= A[i])
            ans++;
    }

    cout << ans << endl;

    return 0;
}