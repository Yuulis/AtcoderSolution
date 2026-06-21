// Prefix Sum (Cumulative Sum) — 1D range sum queries in O(1).
//
// Given an array a[0..n-1], build a prefix sum array S[0..n] where
//   S[0] = 0
//   S[i] = a[0] + a[1] + ... + a[i-1]   (for i >= 1)
//
// Then the sum of elements in the half-open range [l, r) is simply:
//   sum(l, r) = S[r] - S[l]
//
// This works because:
//   S[r] = a[0] + a[1] + ... + a[r-1]
//   S[l] = a[0] + a[1] + ... + a[l-1]
//   S[r] - S[l] = a[l] + a[l+1] + ... + a[r-1]
//
// The key idea is to trade O(n) preprocessing time for O(1) per query.
// Without prefix sums, each range sum query takes O(n) worst case.
//
// Time:  O(n) to build, O(1) per range sum query.
// Space: O(n) for the prefix sum array.
//
// Typical AtCoder use cases:
//   - Range sum queries on a static (non-modifiable) array.
//   - Checking whether a subarray sum equals a target.
//   - Combined with binary search: "find the shortest subarray with sum >= K".
//   - 2D/3D prefix sums for grid problems (see comments below).
//
// Caveats:
//   - The array must be static. If elements change, use a Fenwick Tree (BIT)
//     or Segment Tree instead.
//   - Watch for integer overflow: if a[i] can be up to 1e9 and N up to 2e5,
//     the prefix sum can reach ~2e14, which overflows int. Use long long.
//   - Range is half-open [l, r). For a closed interval [l, r], use S[r+1] - S[l].

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// build_prefix_sum: construct the 1D prefix sum array from input array a.
//
// Parameters:
//   a — input array of size n.
//
// Returns:
//   A vector S of size n+1 where S[i] = a[0] + a[1] + ... + a[i-1].
//   S[0] is always 0 (empty prefix).
//
// Example:
//   a = [3, 1, 4, 1, 5]
//   S = [0, 3, 4, 8, 9, 14]
//   sum of a[1..3] = S[4] - S[1] = 9 - 3 = 6 (i.e., 1 + 4 + 1)
vector<ll> build_prefix_sum(const vector<ll> &a) {
    int n = (int)a.size();
    // S has size n+1 so that S[0] = 0 (the empty prefix) and S[n] = total sum.
    vector<ll> S(n + 1, 0);
    for (int i = 0; i < n; i++) {
        S[i + 1] = S[i] + a[i];
    }
    return S;
}

// range_sum: compute the sum of a[l] + a[l+1] + ... + a[r-1] in O(1).
//
// Parameters:
//   S — prefix sum array built by build_prefix_sum.
//   l — left index (inclusive, 0-indexed).
//   r — right index (exclusive, 0-indexed).
//
// Returns:
//   The sum of elements in [l, r).
//
// Precondition: 0 <= l <= r <= n.
ll range_sum(const vector<ll> &S, int l, int r) {
    return S[r] - S[l];
}

// --- Minimal usage example ---
// Input format:
//   N Q
//   a[0] a[1] ... a[N-1]
//   l1 r1     (Q queries, each asking for sum of [l, r) — 0-indexed, half-open)
//   l2 r2
//   ...
int main() {
    int N, Q;
    cin >> N >> Q;

    vector<ll> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    // Build the prefix sum array: O(n).
    vector<ll> S = build_prefix_sum(a);

    // Answer each query in O(1).
    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        // Output the sum of a[l] + a[l+1] + ... + a[r-1].
        cout << range_sum(S, l, r) << endl;
    }

    // --- Note on 2D prefix sums ---
    // For a 2D grid B[H][W], the 2D prefix sum P[i][j] stores the sum of
    // all elements in the rectangle [0,0) to [i,j).
    // Build: P[i+1][j+1] = P[i][j+1] + P[i+1][j] - P[i][j] + B[i][j]
    // Query [r1,c1) to [r2,c2):
    //   P[r2][c2] - P[r1][c2] - P[r2][c1] + P[r1][c1]
    // This extends naturally to 3D with inclusion-exclusion.

    return 0;
}
