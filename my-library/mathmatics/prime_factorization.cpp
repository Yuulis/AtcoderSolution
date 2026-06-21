/*
 * Prime factorization of a positive integer n.
 *
 * Trial-divides n by every integer from 2 up to sqrt(n).
 * Returns a sorted list of (prime, exponent) pairs.
 *
 * Time complexity : O(sqrt(n)).
 * Space complexity: O(log n) for the result (number of distinct primes).
 *
 * Typical use cases:
 *   - Factorizing N to count divisors, compute Euler's totient, etc.
 *   - ABC-C/D problems involving prime structure.
 *   - Checking whether a number is a perfect square / cube.
 *
 * Caveats:
 *   - n must be >= 2 for meaningful output; n = 1 returns an empty vector.
 *   - For n up to ~10^18 this is fine (sqrt fits in long long).
 *   - For many queries with n up to ~10^7, prefer a sieve-based approach
 *     (see linear_sieve.cpp for O(log n) per query).
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Returns a vector of (prime, exponent) pairs such that
// n = p1^e1 * p2^e2 * ... , sorted by prime in ascending order.
vector<pair<ll, ll>> prime_factor(ll n) {
    vector<pair<ll, ll>> res;
    // Trial division: try every candidate divisor from 2 to sqrt(n).
    for (ll i = 2; i * i <= n; i++) {
        if (n % i != 0) continue;
        // Count how many times i divides n.
        ll cnt = 0;
        while (n % i == 0) {
            cnt++;
            n /= i;
        }
        res.push_back({i, cnt});
    }
    // If n > 1 remains, it is a prime factor itself.
    if (n != 1) res.push_back({n, 1});
    return res;
}

// --- Minimal usage example ---
int main() {
    ll n = 360; // 360 = 2^3 * 3^2 * 5^1

    vector<pair<ll, ll>> factors = prime_factor(n);

    cout << n << " =";
    for (auto &[p, e] : factors) {
        cout << " " << p << "^" << e;
    }
    cout << endl;
    // Expected output: 360 = 2^3 3^2 5^1

    return 0;
}
