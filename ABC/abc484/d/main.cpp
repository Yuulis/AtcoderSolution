#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];

    map<int, int> mp;
    ll ans = 1;
    rep(i, 0, N)
    {
        if (i == 0 || A[i - 1] != A[i])
        {
            ans += i - mp[A[i]];
        }

        mp[A[i]]++;
    }

    cout << ans << endl;

    return 0;
}