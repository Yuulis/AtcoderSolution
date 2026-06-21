/*
 * Linear sieve computing smallest prime factor (SPF) and prime list.
 *
 * Each composite number is marked exactly once (by its smallest prime
 * factor), achieving true O(N) time.  The SPF table enables O(log n)
 * factorization of any n <= N.
 *
 * Time complexity : O(N) for sieve construction.
 *                   O(log n) per factorization query.
 * Space complexity: O(N).
 *
 * Typical use cases:
 *   - Need to factorize MANY numbers up to N (ABC-D/E level).
 *   - Precomputing prime lists for number-theory problems.
 *   - Faster alternative to Eratosthenes when both prime list and
 *     factorization are needed.
 *
 * Caveats:
 *   - Requires O(N) memory for the SPF array; for N > ~10^8 this is large.
 *   - spf[0] and spf[1] are set to 0 and 1 respectively (neither is prime).
 *
 * How the linear sieve works:
 *   For each i from 2 to N:
 *     1. If spf[i] == 0, then i is prime; set spf[i] = i and add to list.
 *     2. For each prime p in the list (p <= spf[i] and i*p <= N):
 *        - Set spf[i*p] = p.
 *        - If p == spf[i], stop (ensures each composite is hit once).
 *   This guarantees every composite c is marked exactly once, by its
 *   smallest prime factor.
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// spf[i] = smallest prime factor of i (0 for i < 2).
vector<int> spf;
// List of all primes up to N, in ascending order.
vector<int> primes;

// Build the linear sieve for integers in [0, N].
void linear_sieve(int N) {
    spf.assign(N + 1, 0);
    primes.clear();

    for (int i = 2; i <= N; i++) {
        // If spf[i] is still 0, i has no smaller factor → i is prime.
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        // Mark composites i * p for each prime p.
        for (int j = 0; j < (int)primes.size(); j++) {
            int p = primes[j];
            if (p > spf[i] || (ll)i * p > N) break;
            spf[i * p] = p;
        }
    }
}

// Factorize n using the precomputed SPF table.
// Returns a sorted vector of (prime, exponent) pairs.
// Requires n <= N (the sieve limit).
vector<pair<int, int>> factorize(int n) {
    vector<pair<int, int>> res;
    while (n > 1) {
        int p = spf[n];
        int cnt = 0;
        // Divide out all copies of the smallest prime factor.
        while (n > 1 && spf[n] == p) {
            cnt++;
            n /= p;
        }
        res.push_back({p, cnt});
    }
    return res;
}

// --- Minimal usage example ---
int main() {
    int N = 50;
    linear_sieve(N);

    // Print all primes up to N.
    cout << "Primes up to " << N << ":";
    for (int p : primes) {
        cout << " " << p;
    }
    cout << endl;
    // Expected: 2 3 5 7 11 13 17 19 23 29 31 37 41 43 47

    // Factorize 360 = 2^3 * 3^2 * 5.
    // (Need sieve up to at least 360 for this.)
    linear_sieve(400);
    int val = 360;
    auto factors = factorize(val);
    cout << val << " =";
    for (auto &[p, e] : factors) {
        cout << " " << p << "^" << e;
    }
    cout << endl;

    return 0;
}
