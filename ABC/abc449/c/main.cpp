#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N, L, R;
    string S;
    cin >> N >> L >> R >> S;

    vector<vector<int>> pos(26);
    rep(i, 0, N)
    {
        pos[S[i] - 'a'].push_back(i);
    }

    ll ans = 0;
    rep(i, 0, N)
    {
        int c = S[i] - 'a';

        int l = i + L;
        int r = i + R;

        auto itr_l = lower_bound(all(pos[c]), l);
        auto itr_r = upper_bound(all(pos[c]), r);

        ans += (itr_r - itr_l);
    }

    cout << ans << endl;

    return 0;
}