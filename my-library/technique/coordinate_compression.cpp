// Coordinate Compression — map large/sparse values to dense ranks.
//
// Coordinate compression maps a set of N values (possibly large or negative)
// to consecutive integers 0, 1, 2, ..., M-1 where M is the number of distinct
// values. This is essential when values are used as array indices but the value
// range is too large (e.g., up to 1e9) to allocate directly.
//
// Algorithm:
//   1. Copy the values into a separate array.
//   2. Sort the copy.
//   3. Remove duplicates with std::unique + erase.
//   4. For each original value, find its rank using std::lower_bound.
//
// Time:  O(N log N) for sorting + O(N log M) for rank lookups.
// Space: O(N) for the sorted unique array.
//
// Typical AtCoder use cases:
//   - Using values as indices for a Fenwick Tree (BIT) or segment tree when
//     the value range is up to 1e9 but N is at most 2e5.
//   - Discretizing coordinates for sweep line algorithms.
//   - Mapping strings or pairs to dense indices.
//
// Caveats:
//   - The compressed ranks are 0-indexed. If you need 1-indexed (e.g., for
//     a Fenwick Tree), add 1 to each rank.
//   - The relative order of values is preserved (it's a stable mapping).
//   - Original values can be recovered from ranks using the sorted unique array.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// compress: perform coordinate compression on the input array.
//
// Parameters:
//   a — input array of values (may contain duplicates, may be unsorted).
//
// Returns:
//   A pair of:
//     - ranks: vector where ranks[i] is the compressed rank of a[i] (0-indexed).
//     - sorted_unique: the sorted array of distinct values (for decompression).
//
// Example:
//   a = [100, 3, 100, 7, 3]
//   sorted_unique = [3, 7, 100]
//   ranks = [2, 0, 2, 1, 0]
//   (3 → rank 0, 7 → rank 1, 100 → rank 2)
pair<vector<int>, vector<ll>> compress(const vector<ll> &a) {
    int n = (int)a.size();

    // Step 1: Copy the values. We need the original array intact.
    vector<ll> sorted_unique = a;

    // Step 2: Sort the copy.
    sort(sorted_unique.begin(), sorted_unique.end());

    // Step 3: Remove consecutive duplicates.
    // std::unique moves duplicates to the end and returns an iterator to the
    // new logical end. erase() removes the leftover elements.
    sorted_unique.erase(unique(sorted_unique.begin(), sorted_unique.end()),
                        sorted_unique.end());

    // Step 4: Map each original value to its rank via binary search.
    // lower_bound finds the position of a[i] in the sorted unique array,
    // which is exactly its compressed rank (0-indexed).
    vector<int> ranks(n);
    for (int i = 0; i < n; i++) {
        ranks[i] = (int)(lower_bound(sorted_unique.begin(), sorted_unique.end(), a[i])
                         - sorted_unique.begin());
    }

    return {ranks, sorted_unique};
}

// --- Minimal usage example ---
// Input format:
//   N
//   a[0] a[1] ... a[N-1]
// Output: the compressed ranks for each element.
int main() {
    int N;
    cin >> N;

    vector<ll> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    auto [ranks, sorted_unique] = compress(a);

    // Output the compressed ranks (0-indexed).
    for (int i = 0; i < N; i++) {
        cout << ranks[i] << (i + 1 < N ? " " : "\n");
    }

    // To recover original values from ranks:
    // original_value = sorted_unique[rank]
    // For example, sorted_unique[ranks[0]] == a[0].

    return 0;
}
