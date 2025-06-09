#include <bits/stdc++.h>

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using namespace std;

// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];

    int ans = 0;
    rep(x, 0, N + 1)
    {
        int cnt = 0;
        rep(i, 0, N)
        {
            if (A[i] >= x)
                cnt++;
        }

        if (cnt >= x)
            ans = x;
    }

    cout << ans << endl;

    return 0;
}
