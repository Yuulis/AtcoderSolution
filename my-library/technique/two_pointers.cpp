// Two Pointers / Sliding Window — enumerate subarrays satisfying a monotone condition.
//
// The two pointers technique (also called "shakutori method" / "caterpillar method"
// in Japanese competitive programming) efficiently enumerates contiguous subarrays
// [left, right) that satisfy a monotone condition.
//
// Key idea:
//   Maintain two pointers left and right, both starting at 0. For each left,
//   extend right as far as possible while a condition holds, then process the
//   valid window [left, right). When left advances, the window shrinks and we
//   may need to update running state (e.g., subtract a[left] from a sum).
//
// Monotonicity requirement:
//   The condition must be monotone in the following sense:
//   "If the window [left, right) violates the condition, then [left, right+1)
//    also violates it." In other words, extending the window only makes it
//   harder to satisfy the condition. This guarantees that right never decreases,
//   so the total work is O(N).
//
// Common patterns:
//   Pattern A: "Count subarrays with sum < K" (or sum <= K, max - min <= K, etc.)
//     For each left, find the maximum right such that the window is valid.
//     The number of valid subarrays starting at left is (right - left).
//
//   Pattern B: "Find the minimum-length subarray with sum >= K"
//     For each right, shrink left as much as possible while the condition holds.
//
// Time:  O(N) — each pointer moves at most N times total.
// Space: O(1) extra (excluding the input array).
//
// Typical AtCoder use cases:
//   - Count subarrays where sum/max/distinct-count satisfies a bound.
//   - Find shortest/longest subarray satisfying a condition.
//   - String problems: longest substring with at most K distinct characters.
//
// Caveats:
//   - The condition MUST be monotone. If extending the window can both satisfy
//     and violate the condition, two pointers does not work.
//   - Be careful with the initial state: right starts at left (or 0), and the
//     running state must be consistent with the current window.
//   - When left == right (empty window), make sure right advances at least to
//     left + 1 (or handle the edge case explicitly).

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// count_subarrays_sum_less_than_k: count the number of contiguous subarrays
// whose sum is strictly less than K.
//
// Parameters:
//   a — input array of NON-NEGATIVE integers (monotonicity requires this).
//   K — the upper bound (exclusive) for the subarray sum.
//
// Returns:
//   The total count of subarrays [l, r) with sum(a[l..r-1]) < K.
//
// How it works:
//   For each left, right is the maximum index such that sum(a[left..right-1]) < K.
//   All subarrays [left, left+1), [left, left+2), ..., [left, right) are valid,
//   contributing (right - left) subarrays.
//
//   When left advances to left+1, we subtract a[left] from the running sum.
//   Since a[left] >= 0, the sum can only decrease, so right does not need to
//   move backward. This is why right never decreases and the total is O(N).
ll count_subarrays_sum_less_than_k(const vector<ll> &a, ll K) {
    int n = (int)a.size();
    ll count = 0;
    ll sum = 0;
    int right = 0;

    for (int left = 0; left < n; left++) {
        // Extend right as far as possible while the window sum < K.
        while (right < n && sum + a[right] < K) {
            sum += a[right];
            right++;
        }

        // Now [left, right) is the maximal valid window starting at left.
        // All sub-windows [left, left+1), ..., [left, right) are valid.
        count += (right - left);

        // Prepare to advance left: shrink the window by removing a[left].
        if (right == left) {
            // Empty window: just move right forward with left.
            right++;
        } else {
            // Remove a[left] from the running sum.
            sum -= a[left];
        }
    }

    return count;
}

// min_length_subarray_sum_at_least_k: find the minimum-length contiguous subarray
// whose sum is at least K.
//
// Parameters:
//   a — input array of NON-NEGATIVE integers.
//   K — the lower bound (inclusive) for the subarray sum.
//
// Returns:
//   The minimum length of a subarray with sum >= K, or N+1 if none exists.
//
// How it works (Pattern B):
//   Extend right one step at a time. After each extension, shrink left as much
//   as possible while the sum remains >= K. Track the minimum window length.
int min_length_subarray_sum_at_least_k(const vector<ll> &a, ll K) {
    int n = (int)a.size();
    int ans = n + 1;  // sentinel: larger than any valid answer
    ll sum = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        sum += a[right];

        // Shrink from the left while the condition still holds.
        while (sum >= K) {
            ans = min(ans, right - left + 1);
            sum -= a[left];
            left++;
        }
    }

    return ans;
}

// --- Minimal usage example ---
// Input format:
//   N K
//   a[0] a[1] ... a[N-1]   (non-negative integers)
// Output:
//   Number of subarrays with sum < K
//   Minimum length of subarray with sum >= K (or -1 if none)
int main() {
    int N;
    ll K;
    cin >> N >> K;

    vector<ll> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    // Pattern A: count subarrays with sum < K
    ll cnt = count_subarrays_sum_less_than_k(a, K);
    cout << "Subarrays with sum < " << K << ": " << cnt << endl;

    // Pattern B: minimum-length subarray with sum >= K
    int minlen = min_length_subarray_sum_at_least_k(a, K);
    if (minlen <= N)
        cout << "Min length subarray with sum >= " << K << ": " << minlen << endl;
    else
        cout << "No subarray with sum >= " << K << endl;

    return 0;
}
