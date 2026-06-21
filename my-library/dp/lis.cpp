// Longest Increasing Subsequence (LIS) — O(N log N) with binary search.
//
// Finds the length of the longest strictly increasing subsequence of an array.
// The algorithm maintains a list `tails` where tails[i] is the smallest possible
// tail element of an increasing subsequence of length i+1 found so far.
//
// Key insight: `tails` is always sorted in increasing order. This allows us to
// use binary search (lower_bound) to find where each new element should go:
//   - If a[j] > tails.back(), it extends the longest subsequence: push_back.
//   - Otherwise, replace the first element in tails that is >= a[j].
//     This doesn't change the LIS length but keeps tails as small as possible,
//     maximizing future extension opportunities.
//
// Strictly increasing vs non-strictly increasing:
//   - Strictly increasing (a[i] < a[j] for i < j):
//     Use lower_bound to find the first tails element >= a[j], and replace it.
//   - Non-strictly increasing (a[i] <= a[j] for i < j):
//     Use upper_bound to find the first tails element > a[j], and replace it.
//     This allows equal elements to coexist in the subsequence.
//
// Time:  O(N log N) — one binary search per element.
// Space: O(N) for the tails array.
//
// Typical AtCoder use cases:
//   - Direct LIS problems (ABC, ARC).
//   - Problems reducible to LIS (e.g., minimum number of non-crossing segments).
//   - Longest non-decreasing subsequence (use upper_bound variant).
//
// Caveats:
//   - This algorithm finds the LENGTH of the LIS, not the subsequence itself.
//     To reconstruct the actual subsequence, track predecessor indices.
//   - `tails` at the end does NOT represent an actual subsequence — it's an
//     auxiliary structure. Don't output it as the answer.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// lis_length: compute the length of the longest strictly increasing subsequence.
//
// Parameters:
//   a — input array.
//
// Returns:
//   The length of the LIS.
//
// How it works step by step:
//   Maintain tails[] = smallest tail of IS of each length.
//   For each element x in a:
//     - Binary search tails for the first value >= x (lower_bound).
//     - If found at position pos, replace tails[pos] = x (we found a better tail).
//     - If not found (x > all tails), append x (IS length increases by 1).
//   The final answer is tails.size().
//
// Example:
//   a = [3, 1, 4, 1, 5, 9, 2, 6]
//   Processing:
//     3 → tails = [3]
//     1 → tails = [1]          (replace 3 with 1)
//     4 → tails = [1, 4]       (extend)
//     1 → tails = [1, 4]       (replace 1 with 1, no change)
//     5 → tails = [1, 4, 5]    (extend)
//     9 → tails = [1, 4, 5, 9] (extend)
//     2 → tails = [1, 2, 5, 9] (replace 4 with 2)
//     6 → tails = [1, 2, 5, 6] (replace 9 with 6)
//   Answer: 4 (e.g., subsequence [1, 4, 5, 9] or [1, 2, 5, 6])
int lis_length(const vector<ll> &a) {
    vector<ll> tails;

    for (ll x : a) {
        // For STRICTLY increasing: use lower_bound (find first >= x).
        // For NON-STRICTLY increasing: change to upper_bound (find first > x).
        auto it = lower_bound(tails.begin(), tails.end(), x);

        if (it == tails.end()) {
            // x is larger than all current tails → extend the LIS.
            tails.push_back(x);
        } else {
            // Replace *it with x. This keeps tails as small as possible
            // without changing the LIS length, enabling future extensions.
            *it = x;
        }
    }

    // The size of tails equals the LIS length.
    return (int)tails.size();
}

// lis_length_nondecreasing: longest NON-STRICTLY increasing subsequence.
//
// The only difference from the strictly increasing version is using upper_bound
// instead of lower_bound. This allows equal consecutive elements.
//
// Example: a = [3, 1, 1, 2] → LIS (strict) = 2 ([1, 2]), LNIS = 3 ([1, 1, 2])
int lis_length_nondecreasing(const vector<ll> &a) {
    vector<ll> tails;

    for (ll x : a) {
        // upper_bound: find first element STRICTLY GREATER than x.
        // This allows equal elements to be part of the subsequence.
        auto it = upper_bound(tails.begin(), tails.end(), x);

        if (it == tails.end()) {
            tails.push_back(x);
        } else {
            *it = x;
        }
    }

    return (int)tails.size();
}

// --- Minimal usage example ---
// Input format:
//   N
//   a[0] a[1] ... a[N-1]
// Output: LIS length (strictly increasing) and LNIS length (non-decreasing).
int main() {
    int N;
    cin >> N;

    vector<ll> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    cout << "LIS (strictly increasing): " << lis_length(a) << endl;
    cout << "LNIS (non-decreasing):     " << lis_length_nondecreasing(a) << endl;

    return 0;
}
