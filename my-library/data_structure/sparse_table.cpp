/*
 * Sparse Table (Static Range Minimum Query)
 *
 * A data structure for answering range minimum queries on a static array.
 * It exploits the idempotency of the min operation: min(a, a) = a, so
 * overlapping sub-ranges do not cause errors.
 *
 * Build:
 *   For each power-of-two length k = 2^j, precompute the minimum of every
 *   sub-array of that length:
 *     table[j][i] = min( a[i], a[i+1], ..., a[i + 2^j - 1] )
 *   Base case (j = 0): table[0][i] = a[i].
 *   Transition:  table[j][i] = min(table[j-1][i], table[j-1][i + 2^(j-1)]).
 *
 * Query [l, r) (half-open):
 *   Let k = floor(log2(r - l)).
 *   Answer = min(table[k][l], table[k][r - 2^k]).
 *   The two ranges [l, l+2^k) and [r-2^k, r) together cover [l, r),
 *   and overlap is fine because min is idempotent.
 *
 * Time:  O(n log n) build, O(1) query.
 * Space: O(n log n).
 *
 * Typical use cases:
 *   - Static RMQ (no updates to the array).
 *   - Sub-routine in LCA via Euler tour + RMQ.
 *   - Any idempotent associative function (min, max, gcd, bitwise AND/OR).
 *
 * Caveats:
 *   - Does NOT support point updates.  Use a segment tree if updates are needed.
 *   - The binary operation must be idempotent (sum is NOT idempotent).
 *   - Query range is half-open: [l, r).
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
struct SparseTable {
    vector<vector<T>> table;
    vector<int> log_table; // precomputed floor(log2(i))

    SparseTable() {}

    // Build from a given array.
    SparseTable(const vector<T>& a) {
        int n = (int)a.size();

        // Precompute floor(log2(i)) for i = 0..n
        log_table.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            log_table[i] = log_table[i / 2] + 1;
        }

        int LOG = log_table[n] + 1;
        table.assign(LOG, vector<T>(n));

        // Base case: intervals of length 1
        table[0] = a;

        // Fill table using doubling
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[j][i] = min(table[j - 1][i],
                                  table[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    // Query the minimum in [l, r) (0-indexed, half-open).
    T query(int l, int r) const {
        int k = log_table[r - l];
        return min(table[k][l], table[k][r - (1 << k)]);
    }
};

int main() {
    // Example: read N elements and Q queries, answer min over [l, r).
    int N, Q;
    cin >> N >> Q;

    vector<ll> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    SparseTable<ll> st(A);

    while (Q--) {
        int l, r;
        cin >> l >> r; // 0-indexed, half-open [l, r)
        cout << st.query(l, r) << "\n";
    }
    return 0;
}
