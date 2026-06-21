/*
 * GCD (Greatest Common Divisor) and LCM (Least Common Multiple).
 *
 * Provides:
 *   gcd(a, b)        — Euclidean algorithm for two integers.
 *   lcm(a, b)        — Overflow-safe LCM (divides before multiplying).
 *   gcd_vec(v)       — GCD of all elements in a vector.
 *   lcm_vec(v)       — LCM of all elements in a vector.
 *
 * Time complexity : O(log(min(a,b))) per gcd call.
 * Space complexity: O(1) per call (iterative).
 *
 * Typical use cases:
 *   - Computing GCD / LCM of two or more values (ABC-A/B/C level).
 *   - Reducing fractions, finding common periods / cycle lengths.
 *   - Problems like "LCM of an array" where overflow is a concern.
 *
 * Caveats:
 *   - lcm() divides a by gcd(a,b) BEFORE multiplying by b to avoid
 *     intermediate overflow.  Even so, the final LCM itself may overflow
 *     long long if it exceeds ~9.2 * 10^18.
 *   - gcd(0, 0) returns 0 by convention.
 *   - C++17 provides std::gcd / std::lcm in <numeric>, but the std::lcm
 *     is NOT overflow-safe (it multiplies first).  This implementation
 *     is preferred for competitive programming.
 *
 * How the Euclidean algorithm works:
 *   gcd(a, b) repeatedly replaces (a, b) with (b, a % b) until b == 0.
 *   At that point a holds the GCD.
 *   Example: gcd(48, 18) → gcd(18, 12) → gcd(12, 6) → gcd(6, 0) = 6.
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Compute gcd of two non-negative integers using the Euclidean algorithm.
// gcd(a, 0) = a,  gcd(0, 0) = 0.
ll gcd(ll a, ll b) {
    // Take absolute values so that negative inputs are handled correctly.
    a = abs(a);
    b = abs(b);
    // Iteratively replace (a, b) with (b, a % b) until b becomes 0.
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Compute lcm of two non-negative integers.
// OVERFLOW-SAFE: divides by gcd first, then multiplies.
// lcm(a, 0) = 0 by mathematical convention.
ll lcm(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    // Divide before multiplying to prevent intermediate overflow.
    return abs(a) / gcd(a, b) * abs(b);
}

// Compute the GCD of all elements in a vector.
// For an empty vector, returns 0.
ll gcd_vec(const vector<ll> &v) {
    ll result = 0;
    for (ll x : v) {
        result = gcd(result, x);
    }
    return result;
}

// Compute the LCM of all elements in a vector.
// For an empty vector, returns 1 (neutral element of LCM).
// WARNING: the running LCM can overflow long long for large inputs.
ll lcm_vec(const vector<ll> &v) {
    if (v.empty()) return 1;
    ll result = v[0];
    for (int i = 1; i < (int)v.size(); i++) {
        result = lcm(result, v[i]);
    }
    return result;
}

// --- Minimal usage example ---
int main() {
    // Basic GCD and LCM of two numbers.
    cout << "gcd(48, 18) = " << gcd(48, 18) << endl;   // 6
    cout << "lcm(48, 18) = " << lcm(48, 18) << endl;   // 144

    // GCD and LCM over a vector.
    vector<ll> nums = {12, 18, 24};
    cout << "gcd_vec({12,18,24}) = " << gcd_vec(nums) << endl;  // 6
    cout << "lcm_vec({12,18,24}) = " << lcm_vec(nums) << endl;  // 72

    return 0;
}
