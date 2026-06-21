/*
 * Polynomial rolling hash for O(1) substring hash queries after O(n) build.
 *
 * Uses double hashing (two independent mod/base pairs) to minimize collision
 * probability. Each hash is computed as:
 *   hash(s[l..r]) = s[l]*B^(r-l) + s[l+1]*B^(r-l-1) + ... + s[r]  (mod M)
 *
 * Time complexity:  O(n) to build; O(1) per substring hash query.
 * Space complexity: O(n) for prefix hashes and power tables.
 *
 * Typical AtCoder use cases:
 *   - Finding all occurrences of a pattern in a text in O(n + m).
 *   - Comparing arbitrary substrings for equality in O(1) (with high
 *     probability) — useful in binary-search-on-answer + hash problems.
 *   - Longest common substring via binary search + hash set.
 *
 * Caveats:
 *   - ACL provides z_algorithm (and suffix_array) but NOT rolling hash.
 *   - Hash collisions can occur; double hashing makes the probability
 *     negligible (~1e-18 per comparison) but not zero.
 *   - Bases are chosen randomly at runtime to resist anti-hash attacks.
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct RollingHash {
    // Two large primes for double hashing.
    static constexpr ll MOD1 = (1LL << 61) - 1; // Mersenne prime 2^61-1
    static constexpr ll MOD2 = 998244353;        // common NTT prime

    int n;
    vector<ll> h1, h2, pw1, pw2;
    ll base1, base2;

    // Safe modular multiplication for mod close to 2^61.
    // Uses 128-bit multiplication to avoid overflow.
    static ll mul_mod(ll a, ll b, ll mod) {
        return (__int128)a * b % mod;
    }

    // Build hash tables from string s.
    // Bases are randomized to prevent adversarial collision attacks.
    RollingHash(const string &s) : n((int)s.size()),
        h1(n + 1, 0), h2(n + 1, 0), pw1(n + 1, 1), pw2(n + 1, 1) {

        // Random bases in [2, MOD-2] to resist hack/anti-hash tests
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        base1 = uniform_int_distribution<ll>(2, MOD1 - 2)(rng);
        base2 = uniform_int_distribution<ll>(2, MOD2 - 2)(rng);

        // Precompute prefix hashes and power tables
        for (int i = 0; i < n; i++) {
            h1[i + 1] = (mul_mod(h1[i], base1, MOD1) + s[i]) % MOD1;
            h2[i + 1] = (mul_mod(h2[i], base2, MOD2) + s[i]) % MOD2;
            pw1[i + 1] = mul_mod(pw1[i], base1, MOD1);
            pw2[i + 1] = mul_mod(pw2[i], base2, MOD2);
        }
    }

    // Get the hash of substring s[l..r) (0-indexed, half-open interval).
    // Returns a pair of (hash1, hash2) for double hashing.
    // Precondition: 0 <= l <= r <= n.
    pair<ll, ll> get(int l, int r) const {
        ll v1 = (h1[r] - mul_mod(h1[l], pw1[r - l], MOD1) % MOD1 + MOD1) % MOD1;
        ll v2 = (h2[r] - mul_mod(h2[l], pw2[r - l], MOD2) % MOD2 + MOD2) % MOD2;
        return {v1, v2};
    }

    // Check if substring s[l1..r1) equals s[l2..r2) by comparing hashes.
    bool equal(int l1, int r1, int l2, int r2) const {
        return get(l1, r1) == get(l2, r2);
    }
};

// Find all starting positions where pattern occurs in text.
// Returns 0-indexed positions.
vector<int> find_pattern(const string &text, const string &pattern) {
    int n = (int)text.size(), m = (int)pattern.size();
    if (m > n) return {};

    // Build hashes for both strings using the same base.
    // To share bases, concatenate pattern + sentinel + text.
    string combined = pattern + '\0' + text;
    RollingHash rh(combined);

    // Pattern hash is rh.get(0, m)
    auto pat_hash = rh.get(0, m);

    vector<int> positions;
    // Offset in combined string: text starts at index (m + 1)
    int offset = m + 1;
    for (int i = 0; i + m <= n; i++) {
        if (rh.get(offset + i, offset + i + m) == pat_hash) {
            positions.push_back(i);
        }
    }
    return positions;
}

int main() {
    // Example: find all occurrences of "ab" in "ababcab"
    string text = "ababcab";
    string pattern = "ab";

    auto positions = find_pattern(text, pattern);
    cout << "Pattern \"" << pattern << "\" found in \"" << text << "\" at positions:";
    for (int pos : positions) cout << " " << pos;
    cout << endl;
    // Expected output: 0 2 5

    // Example: substring equality check
    string s = "abcabc";
    RollingHash rh(s);
    // s[0..3) = "abc" vs s[3..6) = "abc" -> should be equal
    cout << "s[0..3) == s[3..6): " << (rh.equal(0, 3, 3, 6) ? "yes" : "no") << endl;
    // s[0..3) = "abc" vs s[1..4) = "bca" -> should differ
    cout << "s[0..3) == s[1..4): " << (rh.equal(0, 3, 1, 4) ? "yes" : "no") << endl;

    return 0;
}
