#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define repe(i, start, end) for (auto i = (start); (i) <= (end); (i)++)

using mint = modint998244353;

// ======================================== //

const int MAX = 4000100;
mint fac[MAX], finv[MAX], inv[MAX];

// 前処理
void COMinit()
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

// 二項係数計算
mint COM(int n, int k)
{
    if (n < k)
        return 0;
    if (n < 0 || k < 0)
        return 0;
    return fac[n] * finv[k] * finv[n - k];
}

int main()
{
    int A, B, C, D;
    cin >> A >> B >> C >> D;

    COMinit();

    mint ans = 0;
    repe(k, 0, C)
    {
        mint com1 = COM(A + B + k, B);
        mint com2 = COM((D - 1) + (C - k), (D - 1));
        ans += com1 * com2;
    }

    cout << ans.val() << endl;

    return 0;
}