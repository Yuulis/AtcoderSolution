/*
 * Palindrome check for strings.
 *
 * Time complexity:  O(n) where n = length of the string.
 * Space complexity: O(1) extra (only index variables).
 *
 * Typical AtCoder use cases:
 *   - Checking whether a given string is a palindrome.
 *   - Verifying palindrome properties in substring enumeration problems.
 *   - Combined with construction problems (e.g. "minimum insertions to make
 *     a palindrome").
 *
 * Caveats:
 *   - This performs a simple character-by-character comparison; it does NOT
 *     handle Unicode multi-byte characters (fine for AtCoder which uses ASCII).
 *   - For finding ALL palindromic substrings efficiently, use Manacher's
 *     algorithm instead (O(n)).
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Check whether string s is a palindrome.
// Compares characters from both ends toward the center.
// Returns true if s reads the same forwards and backwards.
bool is_palindrome(const string &s) {
    int n = (int)s.size();
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - 1 - i]) return false;
    }
    return true;
}

// Check whether the substring s[l..r] (inclusive) is a palindrome.
// Precondition: 0 <= l <= r < s.size().
bool is_palindrome_range(const string &s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

int main() {
    // Basic palindrome checks
    cout << "\"racecar\": " << (is_palindrome("racecar") ? "yes" : "no") << endl;
    cout << "\"hello\":   " << (is_palindrome("hello") ? "yes" : "no") << endl;
    cout << "\"a\":       " << (is_palindrome("a") ? "yes" : "no") << endl;
    cout << "\"\":        " << (is_palindrome("") ? "yes" : "no") << endl;

    // Substring palindrome check
    string s = "abacaba";
    // s[2..4] = "aca" -> palindrome
    cout << "\"abacaba\"[2..4]=\"aca\": "
         << (is_palindrome_range(s, 2, 4) ? "yes" : "no") << endl;
    // s[1..3] = "bac" -> not palindrome
    cout << "\"abacaba\"[1..3]=\"bac\": "
         << (is_palindrome_range(s, 1, 3) ? "yes" : "no") << endl;

    return 0;
}
