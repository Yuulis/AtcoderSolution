#include <bits/stdc++.h>
using namespace std;

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
    ll L;
    cin >> L;

    cout << nCk(L - 1, 11) << endl;

    return 0;
}