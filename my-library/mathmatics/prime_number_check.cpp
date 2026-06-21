/*
 * Primality test by trial division.
 *
 * Checks whether a given integer x is prime by testing all potential
 * divisors from 2 up to sqrt(x).
 *
 * Time complexity : O(sqrt(x)).
 * Space complexity: O(1).
 *
 * Typical use cases:
 *   - Quick single-number primality check (ABC-A/B/C level).
 *   - Filtering candidates in brute-force searches.
 *   - Validating input constraints that require a prime.
 *
 * Caveats:
 *   - For checking many numbers up to N, prefer a sieve (O(N log log N)
 *     total) rather than calling is_prime() N times (O(N sqrt(N)) total).
 *   - Works correctly for all long long values (negative → false, 0,1 → false).
 *   - For very large numbers (> 10^18), consider Miller-Rabin instead.
 *
 * How it works:
 *   1. Numbers less than 2 are not prime by definition.
 *   2. For i = 2, 3, ..., while i*i <= x:
 *      - If x is divisible by i, then x is composite → return false.
 *   3. If no divisor is found, x is prime → return true.
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Returns true if x is a prime number, false otherwise.
// Handles edge cases: x < 2 → false.
bool is_prime(ll x) {
    // 0 and 1 are not prime; negative numbers are not prime.
    if (x < 2) return false;

    // Check divisibility by every integer from 2 to sqrt(x).
    // If any divides x evenly, x is not prime.
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    // No divisor found — x is prime.
    return true;
}

// --- Minimal usage example ---
int main() {
    // Test a few values.
    vector<ll> tests = {1, 2, 3, 4, 17, 18, 997, 1000000007};
    for (ll v : tests) {
        cout << v << " : " << (is_prime(v) ? "prime" : "not prime") << endl;
    }
    // Expected:
    //   1 : not prime
    //   2 : prime
    //   3 : prime
    //   4 : not prime
    //   17 : prime
    //   18 : not prime
    //   997 : prime
    //   1000000007 : prime

    return 0;
}
