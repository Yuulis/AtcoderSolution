// 0/1 Knapsack DP — select items to maximize value within a weight capacity.
//
// Given N items, each with a weight w[i] and a value v[i], and a knapsack with
// weight capacity W, select a subset of items (each used at most once) to
// maximize the total value without exceeding the capacity.
//
// This is the classic 0/1 knapsack problem, solved with dynamic programming.
//
// DP definition:
//   dp[j] = maximum total value achievable using items considered so far
//           with total weight exactly j (or at most j, depending on formulation).
//
// Transition (1D rolling array, iterating weight in REVERSE):
//   For each item i with weight w[i] and value v[i]:
//     for j = W down to w[i]:
//       dp[j] = max(dp[j], dp[j - w[i]] + v[i])
//
// Why iterate j in reverse?
//   If we iterate j from 0 to W (forward), then when we compute dp[j],
//   dp[j - w[i]] may already reflect the current item being included.
//   This would allow using item i multiple times (unbounded knapsack).
//   Reverse iteration ensures dp[j - w[i]] still refers to the state
//   WITHOUT item i, enforcing the "at most once" constraint.
//
// Time:  O(N * W) — N items, W capacity.
// Space: O(W) with the 1D rolling array optimization (instead of O(N * W)).
//
// Typical AtCoder use cases:
//   - "Choose items to maximize/minimize value under a capacity constraint."
//   - Subset sum: "Can you pick items to reach exactly weight T?"
//     (Use dp[j] = true/false instead of max value.)
//   - Problems with small W (up to ~1e5) and moderate N.
//
// Caveats:
//   - Time complexity is O(N * W), which is PSEUDO-POLYNOMIAL. If W is up to
//     1e9, this approach is too slow. Consider alternative formulations
//     (e.g., dp on value sum if values are small).
//   - For the unbounded knapsack (items can be used multiple times), iterate
//     j FORWARD instead of reverse.
//   - Integer overflow: if v[i] can be up to 1e9 and N up to 100, the total
//     value can reach 1e11. Use long long for dp.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// knapsack_01: solve the 0/1 knapsack problem.
//
// Parameters:
//   N      — number of items.
//   W      — knapsack weight capacity.
//   weight — weight[i] is the weight of item i (0-indexed).
//   value  — value[i] is the value of item i (0-indexed).
//
// Returns:
//   The maximum total value achievable without exceeding capacity W.
//
// Step-by-step:
//   1. Initialize dp[0..W] = 0 (with 0 items, max value at any capacity is 0).
//   2. For each item i:
//      a. For j = W down to weight[i]:
//         dp[j] = max(dp[j],                    ← don't take item i
//                     dp[j - weight[i]] + value[i])  ← take item i
//   3. Answer is dp[W] (maximum value with capacity W).
//
// Example:
//   N=3, W=5, items: {w=2,v=3}, {w=3,v=4}, {w=4,v=5}
//   dp after item 0: [0, 0, 3, 3, 3, 3]
//   dp after item 1: [0, 0, 3, 4, 4, 7]
//   dp after item 2: [0, 0, 3, 4, 5, 7]
//   Answer: dp[5] = 7 (take items 0 and 1: weight 2+3=5, value 3+4=7)
ll knapsack_01(int N, int W, const vector<int> &weight, const vector<ll> &value) {
    // dp[j] = max value with total weight at most j.
    // Using 1D rolling array: only one row, updated in reverse order.
    vector<ll> dp(W + 1, 0);

    for (int i = 0; i < N; i++) {
        // REVERSE order: j from W down to weight[i].
        // This ensures each item is used at most once.
        // If we went forward, dp[j - weight[i]] might already include item i,
        // effectively allowing unlimited use (unbounded knapsack).
        for (int j = W; j >= weight[i]; j--) {
            // Two choices for item i:
            //   1. Skip: dp[j] stays as is (best without item i).
            //   2. Take: dp[j - weight[i]] + value[i] (add item i's value to
            //            the best solution that leaves room for item i's weight).
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }

    // dp[W] is the maximum value achievable with total weight at most W.
    return dp[W];
}

// --- Minimal usage example ---
// Input format:
//   N W
//   w[0] v[0]
//   w[1] v[1]
//   ...
// Output: the maximum total value.
int main() {
    int N, W;
    cin >> N >> W;

    vector<int> weight(N);
    vector<ll> value(N);
    for (int i = 0; i < N; i++) {
        cin >> weight[i] >> value[i];
    }

    ll ans = knapsack_01(N, W, weight, value);
    cout << ans << endl;

    return 0;
}
