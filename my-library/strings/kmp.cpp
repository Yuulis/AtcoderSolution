/*
 * KMP (Knuth-Morris-Pratt) prefix function and pattern matching.
 *
 * The prefix function (also called failure function) for a string s is an
 * array pi where pi[i] = length of the longest proper prefix of s[0..i]
 * that is also a suffix of s[0..i].
 *
 * Time complexity:  O(n) for prefix function; O(n + m) for pattern matching.
 * Space complexity: O(n) for the prefix function array.
 *
 * Typical AtCoder use cases:
 *   - Finding all occurrences of a pattern in a text.
 *   - Computing the shortest period of a string (period = n - pi[n-1]).
 *   - Counting distinct substrings or prefix-suffix overlaps.
 *   - Building automata for string matching in DP problems.
 *
 * Caveats:
 *   - ACL provides z_algorithm (z-function) but NOT KMP. Both solve similar
 *     problems; KMP is sometimes more natural for automaton-based DP.
 *   - The prefix function is 0-indexed: pi[0] is always 0.
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Compute the prefix function (failure function) for string s.
// pi[i] = length of the longest proper prefix of s[0..i] that is also
// a suffix of s[0..i]. By definition, pi[0] = 0.
//
// Algorithm:
//   Maintain a pointer k tracking the current matched prefix length.
//   For each position i, try to extend the match. If s[i] != s[k],
//   fall back using the prefix function (k = pi[k-1]) until a match
//   is found or k reaches 0.
vector<int> prefix_function(const string &s) {
    int n = (int)s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int k = pi[i - 1];
        // Fall back along the failure chain until we find a match or exhaust
        while (k > 0 && s[i] != s[k]) {
            k = pi[k - 1];
        }
        // If current character matches, extend the prefix length
        if (s[i] == s[k]) k++;
        pi[i] = k;
    }
    return pi;
}

// Find all starting positions (0-indexed) where pattern occurs in text.
// Uses the standard KMP trick: concatenate pattern + sentinel + text,
// then compute the prefix function. Positions where pi[i] == m indicate
// a full match.
vector<int> kmp_search(const string &text, const string &pattern) {
    int n = (int)text.size(), m = (int)pattern.size();
    if (m == 0 || m > n) return {};

    // Concatenate with a sentinel character that appears in neither string.
    // '\0' is safe for typical AtCoder input (printable ASCII).
    string combined = pattern + '\0' + text;
    auto pi = prefix_function(combined);

    vector<int> positions;
    for (int i = m + 1; i < (int)combined.size(); i++) {
        if (pi[i] == m) {
            // Match ends at position i in combined, which corresponds to
            // position (i - m - 1) - m + 1 = i - 2*m in text... let's
            // compute correctly: combined[m+1..] is text, so text index
            // of combined[i] is (i - m - 1). Match starts at text index
            // (i - m - 1) - m + 1 = i - 2*m.
            positions.push_back(i - 2 * m);
        }
    }
    return positions;
}

// Compute the shortest period of string s.
// The shortest period p satisfies: s[i] == s[i % p] for all i.
// p = n - pi[n-1], where n = s.size().
int shortest_period(const string &s) {
    auto pi = prefix_function(s);
    int n = (int)s.size();
    return n - pi[n - 1];
}

int main() {
    // Example 1: Pattern matching
    string text = "ababcababd";
    string pattern = "abab";

    auto positions = kmp_search(text, pattern);
    cout << "Pattern \"" << pattern << "\" found in \"" << text << "\" at positions:";
    for (int pos : positions) cout << " " << pos;
    cout << endl;
    // Expected: 0 5

    // Example 2: Prefix function values
    string s = "aabaaab";
    auto pi = prefix_function(s);
    cout << "Prefix function of \"" << s << "\": ";
    for (int v : pi) cout << v << " ";
    cout << endl;
    // Expected: 0 1 0 1 2 2 3

    // Example 3: Shortest period
    string t = "abcabcabc";
    cout << "Shortest period of \"" << t << "\": " << shortest_period(t) << endl;
    // Expected: 3 (the string is "abc" repeated 3 times)

    return 0;
}
