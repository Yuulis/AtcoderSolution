/*
 * Run-length encoding (RLE) and decoding for strings.
 *
 * Time complexity:  O(n) for encoding; O(sum of counts) for decoding.
 * Space complexity: O(k) where k = number of distinct consecutive groups.
 *
 * Typical AtCoder use cases:
 *   - Compressing consecutive identical characters for simpler processing
 *     (e.g. "aaabbc" -> [('a',3),('b',2),('c',1)]).
 *   - Problems asking "how many groups of consecutive same characters".
 *   - Simulating operations on runs (e.g. removing or merging groups).
 *
 * Caveats:
 *   - Only groups strictly identical adjacent characters. Does not sort or
 *     rearrange the string.
 *   - Encoding an empty string returns an empty vector (not an error).
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Encode a string into run-length form.
// Returns a vector of (character, count) pairs representing consecutive
// groups of identical characters.
// Example: "aaabbc" -> [('a',3), ('b',2), ('c',1)]
vector<pair<char, int>> rle_encode(const string &s) {
    int n = (int)s.size();
    vector<pair<char, int>> res;
    for (int l = 0; l < n;) {
        int r = l + 1;
        while (r < n && s[r] == s[l]) r++;
        res.emplace_back(s[l], r - l);
        l = r;
    }
    return res;
}

// Decode a run-length encoded sequence back into a string.
// Each pair (ch, cnt) expands to cnt copies of ch.
string rle_decode(const vector<pair<char, int>> &code) {
    string res;
    for (auto &[ch, cnt] : code) {
        res.append(cnt, ch);
    }
    return res;
}

int main() {
    string original = "aaabbcddddd";

    // Encode
    auto encoded = rle_encode(original);
    cout << "Encoded: ";
    for (auto &[ch, cnt] : encoded) {
        cout << "('" << ch << "'," << cnt << ") ";
    }
    cout << endl;
    // Output: ('a',3) ('b',2) ('c',1) ('d',5)

    // Decode back
    string decoded = rle_decode(encoded);
    cout << "Decoded: " << decoded << endl;
    // Output: aaabbcddddd

    // Verify round-trip
    cout << "Round-trip OK: " << (original == decoded ? "yes" : "no") << endl;

    return 0;
}
