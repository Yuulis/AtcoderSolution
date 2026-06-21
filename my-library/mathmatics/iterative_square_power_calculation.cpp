/*
 * Fast exponentiation by repeated squaring (binary exponentiation).
 *
 * Provides two variants:
 *   power(x, n)      — computes x^n exactly (no modulus).
 *   power_mod(x,n,m) — computes x^n mod m.
 *
 * Time complexity : O(log n) multiplications.
 * Space complexity: O(1).
 *
 * Typical use cases:
 *   - Computing large powers modulo a prime (ABC-C/D level).
 *   - Fermat's little theorem for modular inverse (a^{p-2} mod p).
 *   - Matrix exponentiation base step.
 *
 * Caveats:
 *   - power() without mod will overflow for large x or n.
 *     Use power_mod() whenever the result would exceed long long range.
 *   - For mod == 1 the result is always 0.
 *   - x, n, mod must be non-negative; n >= 0.
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Compute x^n without modulus.
// WARNING: overflows silently for large values.
ll power(ll x, ll n) {
    ll res = 1;
    while (n > 0) {
        // If the lowest bit of n is 1, multiply result by x.
        if (n & 1) res *= x;
        // Square the base for the next bit.
        x *= x;
        // Shift exponent right by one bit.
        n >>= 1;
    }
    return res;
}

// Compute x^n mod m using repeated squaring.
// Each multiplication is immediately followed by mod to prevent overflow.
ll power_mod(ll x, ll n, ll mod) {
    ll res = 1;
    x %= mod; // Reduce x first in case x >= mod.
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

// --- Minimal usage example ---
int main() {
    // 3^8 = 6561
    cout << power(3, 8) << endl;

    // 2^42 mod 10^9+7 = 46480318 (obtained by Fermat-safe arithmetic)
    cout << power_mod(2, 42, 1000000007) << endl;

    return 0;
}
