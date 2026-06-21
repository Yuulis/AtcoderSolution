/*
 * Enumerate all divisors of a positive integer n.
 *
 * Iterates from 1 to sqrt(n); for each divisor i found,
 * both i and n/i are collected, then sorted in ascending order.
 *
 * Time complexity : O(sqrt(n)) for enumeration + O(d log d) for sorting,
 *                   where d is the number of divisors.
 * Space complexity: O(d).
 *
 * Typical use cases:
 *   - Listing all divisors of N (ABC-C level, e.g. ABC 180-C).
 *   - Brute-forcing over divisors in number-theory problems.
 *   - Counting divisors or checking divisibility conditions.
 *
 * Caveats:
 *   - n must be >= 1.  For n = 0 the behaviour is undefined.
 *   - Works for n up to ~9 * 10^18 (long long range).
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Returns a sorted vector of all positive divisors of n.
vector<ll> calc_divisors(ll n) {
    vector<ll> res;
    // Only iterate up to sqrt(n).
    // If i divides n, then n/i also divides n.
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            // Avoid adding sqrt(n) twice when i*i == n.
            if (i * i != n) {
                res.push_back(n / i);
            }
        }
    }
    sort(res.begin(), res.end());
    return res;
}

// --- Minimal usage example ---
int main() {
    ll n = 60;
    vector<ll> divs = calc_divisors(n);

    // Expected output: 1 2 3 4 5 6 10 12 15 20 30 60
    cout << "Divisors of " << n << ":";
    for (ll d : divs) {
        cout << " " << d;
    }
    cout << endl;

    return 0;
}
