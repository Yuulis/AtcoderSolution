/*
 * Combination (nCk) modular arithmetic using ACL modint.
 *
 * Precomputes factorial, inverse-factorial, and modular inverse tables
 * up to MAX elements so that nCk(n,k) is answered in O(1) per query.
 *
 * Time complexity : O(MAX) precomputation, O(1) per query.
 * Space complexity: O(MAX).
 *
 * Typical use cases:
 *   - Counting paths on a grid (ABC-C/D level).
 *   - Binomial coefficient sums, probability on mod.
 *   - Problems requiring nCk mod p for many (n,k) pairs.
 *
 * Caveats:
 *   - MAX must be larger than the biggest n you query.
 *   - The modulus is set via the mint typedef; change it as needed.
 *   - Only works for prime moduli (modint1000000007 / modint998244353).
 */

#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;
using ll = long long;

// Choose the modulus by commenting/uncommenting:
using mint = modint1000000007;
// using mint = modint998244353;

const int MAX = 510000;

// fac[i]  = i! mod p
// finv[i] = (i!)^{-1} mod p
// inv[i]  = i^{-1} mod p
mint fac[MAX], finv[MAX], inv[MAX];

// Precompute factorial and inverse tables up to MAX-1.
// Uses the recurrence inv[i] = -(p/i) * inv[p%i] mod p,
// which avoids calling pow for every element.
void nCk_init() {
    const int MOD = mint::mod();
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++) {
        fac[i] = fac[i - 1] * i;
        // Recurrence: inv[i] = -(MOD / i) * inv[MOD % i]  (mod MOD)
        inv[i] = MOD - inv[MOD % i] * (MOD / i);
        finv[i] = finv[i - 1] * inv[i];
    }
}

// Returns nCk = n! / (k! * (n-k)!)  mod p.
// Returns 0 when the arguments are out of range.
mint nCk_mod(ll n, ll k) {
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * finv[k] * finv[n - k];
}

// --- Minimal usage example ---
int main() {
    nCk_init();

    // C(100000, 50000) mod 1000000007
    cout << nCk_mod(100000, 50000).val() << endl;

    // C(10, 3) = 120
    cout << nCk_mod(10, 3).val() << endl;

    return 0;
}
