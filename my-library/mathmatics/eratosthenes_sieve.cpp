/*
 * Sieve of Eratosthenes — mark all primes up to N.
 *
 * Builds a boolean table is_prime[] of size N+1.
 * is_prime[i] is true if and only if i is a prime number.
 *
 * Time complexity : O(N log log N).
 * Space complexity: O(N).
 *
 * Typical use cases:
 *   - Precomputing primes for range queries (ABC-C/D level).
 *   - Counting primes up to N.
 *   - Goldbach conjecture verification, prime-pair enumeration.
 *
 * Caveats:
 *   - N must be set before calling sieve().
 *   - For N > ~10^8 the memory may be tight (use bitset or segmented sieve).
 *   - The original code had a bug: vector was sized with uninitialised N.
 *     Fixed by taking N as a parameter and returning the table.
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Returns a boolean vector of size n+1.
// result[i] == true  means i is prime.
// result[0] and result[1] are always false.
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = false;
    if (n >= 1) is_prime[1] = false;

    // Classic Eratosthenes: for each prime p, mark multiples p*2, p*3, ...
    // We only need to check up to sqrt(n).
    for (int i = 2; (ll)i * i <= n; i++) {
        if (is_prime[i]) {
            // Mark all multiples of i starting from 2*i.
            for (int j = 2 * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// --- Minimal usage example ---
int main() {
    int N = 30;
    vector<bool> is_prime = sieve(N);

    // Output all primes up to N.
    // Expected: 2 3 5 7 11 13 17 19 23 29
    cout << "Primes up to " << N << ":";
    for (int i = 2; i <= N; i++) {
        if (is_prime[i]) cout << " " << i;
    }
    cout << endl;

    return 0;
}
