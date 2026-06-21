/*
 * Extended Euclidean algorithm and modular inverse for general modulus.
 *
 * ext_gcd(a, b, x, y) finds integers x, y such that a*x + b*y = gcd(a, b).
 * mod_inverse(a, m)    returns a^{-1} mod m when gcd(a, m) = 1.
 *
 * Time complexity : O(log(min(a, b))).
 * Space complexity: O(log(min(a, b))) due to recursion (can be made iterative).
 *
 * Typical use cases:
 *   - Finding modular inverse when the modulus is NOT prime
 *     (Fermat's little theorem only works for prime moduli).
 *   - Solving linear Diophantine equations a*x + b*y = c.
 *   - Chinese Remainder Theorem (CRT) constructions.
 *
 * Caveats:
 *   - mod_inverse(a, m) requires gcd(a, m) = 1; otherwise it returns -1.
 *   - ACL provides atcoder::inv_mod(a, m) and atcoder::crt() which cover
 *     the same functionality with additional safety checks.
 *   - The returned x may be negative; mod_inverse normalises it to [0, m).
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Extended Euclidean algorithm.
// Given a and b, finds (x, y) such that a*x + b*y = gcd(a, b).
// Returns gcd(a, b).
//
// Recursive formulation:
//   Base case: gcd(a, 0) = a, with x=1, y=0.
//   Recursive step: from gcd(b, a%b) = b*x1 + (a%b)*y1
//     we derive x = y1, y = x1 - (a/b)*y1.
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Modular inverse of a modulo m.
// Returns a value in [0, m) such that (a * result) % m == 1.
// Returns -1 if the inverse does not exist (i.e. gcd(a, m) != 1).
//
// Works for ANY modulus m >= 2 (does not require m to be prime).
// For prime m, Fermat's little theorem (a^{m-2} mod m) is an alternative;
// see modinv.cpp.
ll mod_inverse(ll a, ll m) {
    ll x, y;
    ll g = ext_gcd(a, m, x, y);
    if (g != 1) return -1; // Inverse does not exist.
    // Normalise x into [0, m).
    return (x % m + m) % m;
}

// --- Minimal usage example ---
int main() {
    // ext_gcd example: find x, y such that 35x + 15y = gcd(35,15) = 5.
    ll x, y;
    ll g = ext_gcd(35, 15, x, y);
    cout << "ext_gcd(35, 15): g=" << g
         << ", x=" << x << ", y=" << y << endl;
    // Verify: 35*x + 15*y should equal g.
    cout << "Check: 35*" << x << " + 15*" << y << " = "
         << 35 * x + 15 * y << endl;

    // Modular inverse example: 3^{-1} mod 7 = 5 (since 3*5 = 15 ≡ 1 mod 7).
    cout << "mod_inverse(3, 7) = " << mod_inverse(3, 7) << endl; // 5

    // Non-prime modulus: 3^{-1} mod 10 = 7 (since 3*7 = 21 ≡ 1 mod 10).
    cout << "mod_inverse(3, 10) = " << mod_inverse(3, 10) << endl; // 7

    // No inverse: gcd(2, 4) = 2 ≠ 1.
    cout << "mod_inverse(2, 4) = " << mod_inverse(2, 4) << endl; // -1

    return 0;
}
