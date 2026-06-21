/*
 * Conversion between numeric types and strings in C++.
 *
 * Time complexity:  O(d) per conversion, where d is the number of digits.
 * Space complexity: O(d) for the resulting string / digits.
 *
 * Typical AtCoder use cases:
 *   - Parsing digit-by-digit from a numeric string (e.g. digit DP setup).
 *   - Converting an integer to a string for reversal or palindrome checks.
 *   - Reading mixed numeric/string input and converting between types.
 *
 * Caveats:
 *   - stoi / stoll throw std::out_of_range if the value exceeds the target
 *     type's range. Use stoll for values up to ~9.2e18.
 *   - char-to-int via (ch - '0') only works for '0'..'9'; no validation is
 *     performed here.
 *   - to_string produces decimal representation only (no hex/oct).
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Convert an integer to its decimal string representation.
// Wraps std::to_string for consistency.
string int_to_string(ll n) {
    return to_string(n);
}

// Convert a single digit (0-9) to its character representation.
// Precondition: 0 <= d <= 9.
char digit_to_char(int d) {
    return char(d + '0');
}

// Convert a decimal string to a long long.
// Throws std::invalid_argument if the string is not a valid number.
// Throws std::out_of_range if the value exceeds long long range.
ll string_to_ll(const string &s) {
    return stoll(s);
}

// Convert a digit character ('0'..'9') to its integer value.
// Precondition: '0' <= ch <= '9'.
int char_to_digit(char ch) {
    return int(ch - '0');
}

// Extract each digit from a numeric string into a vector of ints.
// Useful for digit DP or digit-by-digit processing.
// Precondition: every character in s is '0'..'9'.
vector<int> string_to_digits(const string &s) {
    vector<int> digits;
    digits.reserve(s.size());
    for (char ch : s) {
        digits.push_back(char_to_digit(ch));
    }
    return digits;
}

int main() {
    // int -> string
    ll n = 12345;
    string s = int_to_string(n);
    cout << "int_to_string(12345) = \"" << s << "\"" << endl;

    // digit -> char
    cout << "digit_to_char(7) = '" << digit_to_char(7) << "'" << endl;

    // string -> long long (handles leading zeros)
    cout << "string_to_ll(\"0012\") = " << string_to_ll("0012") << endl;

    // char -> digit
    cout << "char_to_digit('9') = " << char_to_digit('9') << endl;

    // string -> digit vector
    vector<int> digits = string_to_digits("12345");
    cout << "string_to_digits(\"12345\") =";
    for (int d : digits) cout << " " << d;
    cout << endl;

    return 0;
}
