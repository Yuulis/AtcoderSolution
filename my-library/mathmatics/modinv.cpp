/*
 * Modular inverse via Fermat's little theorem.
 *
 * For a prime modulus p and a not divisible by p:
 *   a^{-1} ≡ a^{p-2} (mod p)
 *
 * Uses the fast modular exponentiation (repeated squaring) to compute
 * a^{p-2} mod p in O(log p) time.
 *
 * Time complexity : O(log p).
 * Space complexity: O(1).
 *
 * Typical use cases:
 *   - Division under a prime modulus (ABC-C/D level).
 *   - Computing nCk mod p without precomputed inverse tables.
 *   - Any situation requiring a^{-1} mod p where p is prime.
 *
 * Caveats:
 *   - ONLY works when mod is PRIME.  For general (non-prime) modulus,
 *     use the extended Euclidean algorithm (see extended_euclid.cpp).
 *   - a must not be a multiple of mod (otherwise inverse does not exist).
 *   - ACL provides atcoder::inv_mod(a, m) which works for any m and
 *     includes safety checks.  Prefer ACL in contest if available.
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll MOD = 1000000007; // Must be prime for Fermat's theorem.

// Compute x^n mod m using repeated squaring.
// (Same as iterative_square_power_calculation.cpp power_mod.)
ll power_mod(ll x, ll n, ll m) {
    ll res = 1;
    x %= m;
    while (n > 0) {
        if (n & 1) res = res * x % m;
        x = x * x % m;
        n >>= 1;
    }
    return res;
}

// Compute a^{-1} mod p using Fermat's little theorem.
// Requires: p is prime and a is not divisible by p.
// Returns a value in [0, p) such that (a * result) % p == 1.
ll modinv(ll a, ll p = MOD) {
    // a^{p-1} ≡ 1 (mod p)  by Fermat's little theorem.
    // Therefore a^{-1} ≡ a^{p-2} (mod p).
    return power_mod(a, p - 2, p);
}

// --- Minimal usage example ---
int main() {
    // 3^{-1} mod 7 = 5  (since 3 * 5 = 15 ≡ 1 mod 7)
    cout << "modinv(3, 7) = " << modinv(3, 7) << endl; // 5

    // 2^{-1} mod 10^9+7 = 500000004
    cout << "modinv(2) = " << modinv(2) << endl; // 500000004

    // Verify: 2 * 500000004 mod 10^9+7 = 1
    cout << "Check: " << 2LL * modinv(2) % MOD << endl; // 1

    return 0;
}
