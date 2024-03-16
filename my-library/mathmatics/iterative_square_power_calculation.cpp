#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll pow(ll x, ll n)
{
    ll res = 1;
    while (n > 0)
    {
        if (n & 1)
            res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

ll pow_mod(ll x, ll n, ll mod)
{
    ll res = 1;
    while (n > 0)
    {
        if (n & 1)
            res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

// Example
int main()
{
    cout << pow(3, 8) << endl;                  // 6561
    cout << pow_mod(2, 42, 1000000007) << endl; // 46480318
}
