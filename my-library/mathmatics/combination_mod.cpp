#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;
using ll = long long;
using mint = modint1000000007;
// using mint = modint998244353;

const int MAX = 510000;
mint fac[MAX], finv[MAX], inv[MAX];

void nCkInit()
{
    const int MOD = mint::mod();
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++)
    {
        fac[i] = fac[i - 1] * i;
        inv[i] = MOD - inv[MOD % i] * (MOD / i);
        finv[i] = finv[i - 1] * inv[i];
    }
}

mint nCk_mod(ll n, ll k)
{
    if (n < k)
        return 0;
    if (n < 0 || k < 0)
        return 0;
    return fac[n] * finv[k] * finv[n - k];
}

int main()
{
    nCkInit();
    cout << nCk_mod(100000, 50000).val() << endl;
}