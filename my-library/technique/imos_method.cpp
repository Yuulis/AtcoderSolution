// Imos Method (Difference Array) — efficient range-add then snapshot.
//
// The imos method (also known as the "difference array" technique) efficiently
// handles multiple range-add operations on an array, followed by a single
// snapshot to compute the final values.
//
// Key idea:
//   Instead of adding a value to every element in a range (which is O(range_len)
//   per operation), we record only the START and END of each operation in a
//   difference array, then take a prefix sum at the end to recover all values.
//
// For a range-add of +v on the half-open interval [l, r):
//   diff[l]   += v    (the effect starts at index l)
//   diff[r]   -= v    (the effect ends at index r, i.e., does not include r)
//
// After all operations, take the prefix sum of diff[] to get the final array.
//
// Why this works:
//   When we take the prefix sum, the +v at index l propagates to all indices
//   >= l, and the -v at index r cancels it for all indices >= r. So the net
//   effect is +v on exactly [l, r).
//
// Time:  O(Q + N) — O(1) per update, O(N) for the final prefix sum.
// Space: O(N) for the difference array.
//
// Typical AtCoder use cases:
//   - "Add +1 to all elements in [l, r] for Q queries, then output the array."
//   - Schedule overlap counting: "Q intervals are given, find the max overlap."
//   - 2D imos for grid range-add operations.
//
// Caveats:
//   - This is a BATCH technique: you must apply ALL operations first, then
//     take the prefix sum once. You cannot query intermediate states.
//     For online range-add + range-query, use a Fenwick Tree or Lazy Segment Tree.
//   - Watch array bounds: diff must have size N+1 (or N+2 to be safe) because
//     diff[r] may access index N when the range goes up to the last element.
//   - For closed intervals [l, r], use diff[l] += v and diff[r+1] -= v.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// imos_1d: apply Q range-add operations, then compute the final array.
//
// Parameters:
//   n       — size of the array (indices 0 to n-1).
//   queries — list of {l, r, v} meaning "add v to all elements in [l, r)".
//
// Returns:
//   The final array of size n after all range-add operations.
//
// Step-by-step:
//   1. Create a difference array diff[0..n] initialized to 0.
//   2. For each query (l, r, v):
//      - diff[l] += v   (effect starts)
//      - diff[r] -= v   (effect ends)
//   3. Take prefix sum of diff to produce the result array.
vector<ll> imos_1d(int n, const vector<tuple<int, int, ll>> &queries) {
    // diff has size n+1 to safely handle diff[n] when r == n.
    vector<ll> diff(n + 1, 0);

    // Step 1: Record each range-add as a pair of point updates.
    for (auto &[l, r, v] : queries) {
        diff[l] += v;   // add v starting at l
        diff[r] -= v;   // cancel v starting at r
    }

    // Step 2: Prefix sum to recover the actual values.
    // After this, result[i] = sum of all v where l <= i < r.
    vector<ll> result(n);
    ll cumsum = 0;
    for (int i = 0; i < n; i++) {
        cumsum += diff[i];
        result[i] = cumsum;
    }

    return result;
}

// --- Minimal usage example ---
// Input format:
//   N Q
//   l1 r1 v1   (add v1 to [l1, r1), 0-indexed, half-open)
//   l2 r2 v2
//   ...
// Output: the final array after all operations.
int main() {
    int N, Q;
    cin >> N >> Q;

    vector<tuple<int, int, ll>> queries(Q);
    for (int i = 0; i < Q; i++) {
        int l, r;
        ll v;
        cin >> l >> r >> v;
        queries[i] = {l, r, v};
    }

    vector<ll> result = imos_1d(N, queries);

    for (int i = 0; i < N; i++) {
        cout << result[i] << (i + 1 < N ? " " : "\n");
    }

    // --- Note on 2D imos ---
    // For a 2D grid of size H x W, to add v to the rectangle [r1,c1)..[r2,c2):
    //   diff[r1][c1] += v
    //   diff[r1][c2] -= v
    //   diff[r2][c1] -= v
    //   diff[r2][c2] += v
    // Then take row-wise prefix sums, followed by column-wise prefix sums
    // (or vice versa) to recover the final grid.

    return 0;
}
