/*
 * Split a string by a delimiter character.
 *
 * Time complexity:  O(n) where n = length of the input string.
 * Space complexity: O(n) for the resulting tokens.
 *
 * Typical AtCoder use cases:
 *   - Parsing space-separated or comma-separated input.
 *   - Splitting a string into tokens for further processing.
 *   - Handling input formats like "a,b,,c," where empty tokens may or may
 *     not be desired.
 *
 * Caveats:
 *   - split() skips empty tokens by default (consecutive delimiters produce
 *     no empty strings). Use split_keep_empty() if you need them.
 *   - Only supports single-character delimiters. For multi-character
 *     delimiters, use string::find in a loop.
 *
 * Reference: https://marycore.jp/prog/cpp/std-string-split/
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Split string s by delimiter character delim, skipping empty tokens.
// Example: split(",a,b,,c,", ',') -> ["a", "b", "c"]
vector<string> split(const string &s, char delim) {
    // Append a trailing delimiter so that the last field is always captured
    // even when the string ends with the delimiter.
    stringstream ss(s + delim);
    vector<string> tokens;
    string buf;
    while (getline(ss, buf, delim)) {
        if (!buf.empty()) tokens.push_back(buf);
    }
    return tokens;
}

// Split string s by delimiter character delim, keeping empty tokens.
// Example: split_keep_empty(",a,b,,c,", ',') -> ["", "a", "b", "", "c", ""]
vector<string> split_keep_empty(const string &s, char delim) {
    stringstream ss(s);
    vector<string> tokens;
    string buf;
    while (getline(ss, buf, delim)) {
        tokens.push_back(buf);
    }
    return tokens;
}

int main() {
    string s = ",a,b,,c,";

    // Split skipping empty tokens
    auto v1 = split(s, ',');
    cout << "split(\"" << s << "\", ','):" << endl;
    for (auto &tok : v1) cout << "  \"" << tok << "\"" << endl;
    // Output: "a" "b" "c"

    // Split keeping empty tokens
    auto v2 = split_keep_empty(s, ',');
    cout << "split_keep_empty(\"" << s << "\", ','):" << endl;
    for (auto &tok : v2) cout << "  \"" << tok << "\"" << endl;
    // Output: "" "a" "b" "" "c" ""

    return 0;
}
