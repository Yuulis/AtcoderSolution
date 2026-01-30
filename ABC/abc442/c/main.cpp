#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

ll nCk(ll n, ll r)
{
    if (r < 0 || n < r)
        return 0;
    ll ans = 1;
    for (ll i = 1; i <= r; i++)
    {
        ans *= n--;
        ans /= i;
    }
    return ans;
}

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> degs(N, 0);
    rep(i, 0, M)
    {
        int A, B;
        cin >> A >> B;
        A--;
        B--;
        degs[A]++;
        degs[B]++;
    }

    rep(i, 0, N)
    {
        ll x = N - 1 - degs[i];
        if (x < 3)
            cout << 0 << endl;
        else
            cout << nCk(x, 3) << endl;
    }

    return 0;
}