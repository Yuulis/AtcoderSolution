// Binary Search — "Meguru-style" and standard library variants.
//
// Binary search finds the boundary point where a monotone predicate changes
// from false to true (or vice versa). The key insight is that if check(x) is
// monotone (once it becomes true, it stays true for all larger x), then we can
// locate the exact boundary in O(log n) steps.
//
// This file covers three variants:
//   1. Meguru-style integer binary search (ok/ng with a check predicate)
//   2. std::lower_bound / std::upper_bound usage
//   3. Real-valued (double) binary search with fixed iteration count
//
// Time:  O(log n) for integer search on range of size n.
//        O(log(range / eps)) for real-valued search, but we use fixed ~100 iters.
// Space: O(1) extra (excluding the input array).
//
// Typical AtCoder use cases:
//   - "Find the minimum/maximum value satisfying a condition" (answer binary search).
//   - Finding insertion position in a sorted array.
//   - Optimization problems where the answer is monotone in some parameter.
//   - Real-valued binary search for geometry, physics simulation problems.
//
// Caveats:
//   - The predicate MUST be monotone. If check(x) is not monotone, binary
//     search gives wrong answers silently — always verify monotonicity first.
//   - For integer search, be careful with initial ok/ng values: they must
//     bracket the answer. ok must satisfy the predicate; ng must NOT.
//   - For real-valued search, avoid using an epsilon-based loop termination
//     (while (ok - ng > eps)) because floating point errors can cause infinite
//     loops. Use a fixed iteration count instead (60-100 iterations give
//     precision well beyond 1e-9).

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ============================================================
// 1. Meguru-style integer binary search
// ============================================================
//
// The "Meguru-style" binary search maintains two variables:
//   ok  — a value known to satisfy the predicate check()
//   ng  — a value known to NOT satisfy check()
//
// Invariant: check(ok) == true, check(ng) == false, at all times.
//
// The loop narrows the gap between ok and ng until |ok - ng| == 1,
// at which point ok is the boundary (the "first" value satisfying check,
// or the "last" depending on how you set up ok and ng).
//
// How to choose initial ok and ng:
//   - ok must be a value where the predicate is definitely TRUE.
//     Often this is the upper bound + 1 (or lower bound - 1).
//   - ng must be a value where the predicate is definitely FALSE.
//     Often this is the lower bound - 1 (or upper bound + 1).
//   - ok and ng can be on either side: ok < ng or ok > ng both work!
//     The loop condition uses abs(ok - ng) > 1, so it handles both.
//
// Example: "Find the smallest index i such that a[i] >= key"
//   - check(mid) = (a[mid] >= key)
//   - ok = N (out of bounds, but a[N] is "infinitely large" conceptually)
//   - ng = -1 (out of bounds, predicate is false)
//   - After the loop, ok is the answer (equivalent to lower_bound).

// check: the monotone predicate to evaluate.
//
// This example checks whether a[index] >= key, which is monotone on a sorted
// array: once true at some index, it remains true for all larger indices.
//
// For "answer binary search" problems, replace this with your problem-specific
// predicate. For example:
//   - "Can we achieve the task with parameter mid?" (feasibility check)
//   - "Is the answer at most mid?" (upper bound search)
bool check(const vector<ll> &a, ll index, ll key) {
    return a[index] >= key;
}

// meguru_binary_search: find the boundary where check() transitions.
//
// Parameters:
//   a   — sorted array to search in.
//   key — the value to search for.
//
// Returns:
//   The smallest index i such that a[i] >= key (like lower_bound).
//   Returns a.size() if no such index exists.
//
// How the loop works step by step:
//   1. Compute mid = (ok + ng) / 2. This is the midpoint.
//      Note: integer division rounds toward zero, which is fine here because
//      ok and ng always straddle the boundary.
//   2. Evaluate check(mid):
//      - If true, the boundary is at mid or to the left → move ok to mid.
//      - If false, the boundary is to the right → move ng to mid.
//   3. Repeat until |ok - ng| == 1. Now ok is the exact boundary.
ll meguru_binary_search(const vector<ll> &a, ll key) {
    // ok: predicate is TRUE here. We use N (past the end), because
    // conceptually a[N] = +infinity >= key is always true.
    ll ok = (ll)a.size();

    // ng: predicate is FALSE here. We use -1 (before the start), because
    // there is no element at index -1, so the predicate is false.
    ll ng = -1;

    // Loop until ok and ng are adjacent (difference is exactly 1).
    // At that point, ok is the first index where check() is true.
    while (abs(ok - ng) > 1) {
        ll mid = (ok + ng) / 2;

        if (check(a, mid, key))
            ok = mid;   // mid satisfies predicate → boundary is at mid or left
        else
            ng = mid;   // mid doesn't satisfy → boundary is to the right
    }

    // ok is now the smallest index where check() returns true.
    return ok;
}

// ============================================================
// 2. std::lower_bound / std::upper_bound
// ============================================================
//
// The C++ standard library provides binary search on sorted ranges:
//
// lower_bound(first, last, value):
//   Returns an iterator to the FIRST element >= value.
//   Equivalent to meguru_binary_search with check = (a[mid] >= value).
//
// upper_bound(first, last, value):
//   Returns an iterator to the FIRST element > value (strictly greater).
//   Equivalent to meguru_binary_search with check = (a[mid] > value).
//
// Key relationships:
//   - Number of elements < value:  lower_bound - begin
//   - Number of elements <= value: upper_bound - begin
//   - Number of elements == value: upper_bound - lower_bound
//   - To check if value exists: *lower_bound == value (and it != end)

// ============================================================
// 3. Real-valued (double) binary search
// ============================================================
//
// For problems where the answer is a real number (e.g., "find the minimum
// radius such that all points are covered"), we use binary search on doubles.
//
// IMPORTANT: Do NOT use "while (hi - lo > eps)" as the loop condition!
// When lo and hi are large (e.g., 1e18), lo + eps == lo due to floating
// point precision, causing an infinite loop.
//
// Instead, use a fixed number of iterations. Each iteration halves the
// interval, so 100 iterations give precision of (hi - lo) / 2^100,
// which is far beyond what any problem requires (even for range 1e18,
// 2^100 ≈ 1e30 gives precision ~1e-12).
//
// check_real: example predicate for real-valued binary search.
// Replace with your problem-specific feasibility check.
bool check_real(double mid) {
    // Example: "Is it feasible with parameter mid?"
    // Replace this with actual logic.
    return mid * mid >= 2.0;  // Example: find sqrt(2)
}

// real_binary_search: find the boundary value for a real-valued predicate.
//
// Parameters:
//   lo — lower bound (predicate is false here)
//   hi — upper bound (predicate is true here)
//
// Returns:
//   The approximate boundary value (precision ~1e-12 for typical ranges).
double real_binary_search(double lo, double hi) {
    // 100 iterations is more than enough: 2^100 ≈ 1.27e30.
    // Even for a range of 1e18, this gives precision ~1e-12.
    for (int iter = 0; iter < 100; iter++) {
        double mid = (lo + hi) / 2.0;

        if (check_real(mid))
            hi = mid;   // predicate true → answer is at mid or below
        else
            lo = mid;   // predicate false → answer is above mid
    }
    return hi;  // or lo; they are essentially equal after 100 iterations
}

// --- Minimal usage example ---
// Input format:
//   N Q
//   a[0] a[1] ... a[N-1]   (will be sorted)
//   key1 key2 ... keyQ      (Q queries: find first index >= key)
int main() {
    int N, Q;
    cin >> N >> Q;

    vector<ll> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    // Binary search requires a sorted array.
    sort(a.begin(), a.end());

    // --- Meguru-style binary search ---
    cout << "=== Meguru-style ===" << endl;
    for (int i = 0; i < Q; i++) {
        ll key;
        cin >> key;

        ll idx = meguru_binary_search(a, key);
        if (idx < N)
            cout << "First index >= " << key << ": " << idx
                 << " (value = " << a[idx] << ")" << endl;
        else
            cout << "No element >= " << key << endl;
    }

    // --- std::lower_bound / upper_bound ---
    cout << "=== std::lower_bound / upper_bound ===" << endl;
    ll val = a[0];  // Example: search for the first element

    // lower_bound: first element >= val → iterator
    auto lb = lower_bound(a.begin(), a.end(), val);
    cout << "lower_bound(" << val << ") at index " << (lb - a.begin()) << endl;

    // upper_bound: first element > val → iterator
    auto ub = upper_bound(a.begin(), a.end(), val);
    cout << "upper_bound(" << val << ") at index " << (ub - a.begin()) << endl;

    // Count of elements equal to val:
    cout << "count of " << val << ": " << (ub - lb) << endl;

    // --- Real-valued binary search ---
    cout << "=== Real-valued binary search ===" << endl;
    // Example: find sqrt(2) by binary-searching for the smallest x with x^2 >= 2.
    double ans = real_binary_search(0.0, 2.0);
    cout << fixed << setprecision(15);
    cout << "sqrt(2) ≈ " << ans << endl;

    return 0;
}
