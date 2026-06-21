// Floyd-Warshall Algorithm — all-pairs shortest path.
//
// Computes shortest distances between ALL pairs of vertices.
// Can handle negative edge weights (but not negative cycles, although it
// can detect them).
//
// Time:  O(V^3)    — three nested loops over V vertices.
// Space: O(V^2)    — the distance matrix.
//
// Typical AtCoder use cases:
//   - All-pairs shortest path when V is small (V <= 400 or so).
//   - Problems that query distances between many pairs.
//   - Transitive closure (reachability between all pairs).
//
// Caveats:
//   - Only feasible for small V due to O(V^3) time. V <= 400 is typical.
//   - Negative cycle detection: after running, if dist[i][i] < 0 for any i,
//     then vertex i lies on a negative cycle.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll INFL = 1LL << 60;

// floyd_warshall: compute all-pairs shortest distances in-place.
//
// Parameters:
//   dist — V x V matrix. dist[i][j] should be initialized to:
//          0      if i == j,
//          w      if there is a direct edge from i to j with weight w,
//          INFL   otherwise (no direct edge).
//   V    — number of vertices.
//
// After execution, dist[i][j] holds the shortest distance from i to j.
// If dist[i][i] < 0, vertex i is on a negative cycle.
//
// Algorithm:
//   For each intermediate vertex k (0..V-1), try to improve every pair (i, j)
//   by going through k: dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]).
//   The key insight is that after processing intermediate vertices {0..k},
//   dist[i][j] is the shortest path using only vertices {0..k} as intermediates.
void floyd_warshall(vector<vector<ll>> &dist, int V) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] == INFL || dist[k][j] == INFL) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

// --- Minimal usage example ---
// Input: N M, then M lines of (u v cost) for directed edges.
int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<ll>> dist(N, vector<ll>(N, INFL));
    for (int i = 0; i < N; i++) dist[i][i] = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        ll cost;
        cin >> u >> v >> cost;
        dist[u][v] = min(dist[u][v], cost);  // Handle multi-edges: keep shortest.
    }

    floyd_warshall(dist, N);

    // Check for negative cycles.
    for (int i = 0; i < N; i++) {
        if (dist[i][i] < 0) {
            cout << "NEGATIVE CYCLE" << endl;
            return 0;
        }
    }

    // Output the distance matrix.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j > 0) cout << " ";
            if (dist[i][j] == INFL)
                cout << "INF";
            else
                cout << dist[i][j];
        }
        cout << endl;
    }

    return 0;
}
