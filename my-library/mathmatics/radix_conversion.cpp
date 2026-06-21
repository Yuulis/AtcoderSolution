/*
 * Radix (base) conversion between arbitrary bases 2..16.
 *
 * Converts a number represented as a string in one base to a string in
 * another base.  Digits use 0-9 and a-f for values 10-15.
 *
 * Time complexity : O(|x| + log_{to}(value))  where |x| is the input length.
 * Space complexity: O(log_{to}(value)) for the output string.
 *
 * Typical use cases:
 *   - Decimal ↔ binary / hex conversion (ABC-A/B level).
 *   - Problems requiring base-k digit sums or digit enumeration.
 *
 * Caveats:
 *   - Only supports bases 2 through 16.
 *   - The intermediate value is stored in unsigned long long, so the
 *     input number must fit in that range (up to ~1.8 * 10^19).
 *   - Negative numbers are not handled; strip and re-attach the sign
 *     if needed.
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Convert a number string x from base `from` to base `to`.
// Digits are taken from the table "0123456789abcdef".
// Asserts that both bases are in [2, 16].
string radix_conversion(const string &x, int from, int to) {
    // Lookup table: character ↔ digit value.
    const string table = "0123456789abcdef";
    assert(2 <= from && from <= 16);
    assert(2 <= to && to <= 16);

    // Step 1: Convert input string from source base to a decimal integer.
    // Process each character left-to-right using Horner's method.
    unsigned long long sum = 0;
    for (char c : x) {
        sum = sum * from + table.find(c);
    }

    // Step 2: Convert the decimal integer to the target base.
    // Repeatedly divide by `to` and collect remainders (least-significant first).
    string res;
    do {
        int mod = sum % to;
        res = table[mod] + res;
        sum /= to;
    } while (sum > 0);

    return res;
}

// --- Minimal usage example ---
int main() {
    // Binary "110" → decimal "6"
    cout << radix_conversion("110", 2, 10) << endl;

    // Decimal "255" → hexadecimal "ff"
    cout << radix_conversion("255", 10, 16) << endl;

    // Hexadecimal "1a" → binary "11010"
    cout << radix_conversion("1a", 16, 2) << endl;

    return 0;
}
