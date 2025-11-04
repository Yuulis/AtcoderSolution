#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

ll f(ll x)
{
    string s = to_string(x);
    ranges::reverse(s);
    return stoll(s);
}

int main()
{
    int X, Y;
    cin >> X >> Y;

    vector<ll> a;
    a.push_back(X);
    a.push_back(Y);

    rep(i, 2, 10) a.push_back(f(a[i - 1] + a[i - 2]));

    cout << a[9] << endl;

    return 0;
}