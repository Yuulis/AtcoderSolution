// Bellman-Ford Algorithm — shortest path allowing negative edges + negative cycle detection.
//
// Computes single-source shortest paths in a graph that may contain negative
// edge weights. Also detects negative cycles reachable from the source.
//
// Time:  O(V * E)  — V-1 relaxation rounds, each scanning all E edges.
// Space: O(V + E)  — distance array + edge list.
//
// Typical AtCoder use cases:
//   - Shortest path when negative edges exist (e.g., profit/loss on edges).
//   - Detecting negative cycles (arbitrage, infinite improvement loops).
//   - Problems where Dijkstra cannot be used due to negative weights.
//
// Caveats:
//   - Much slower than Dijkstra for non-negative graphs.
//   - If a negative cycle is reachable from the source, shortest paths to
//     some vertices may be -infinity. This implementation marks them as such.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll INFL = 1LL << 60;

struct Edge {
    int from, to;
    ll cost;
};

// bellman_ford: compute shortest distances from `start`.
//
// Parameters:
//   edges  — list of all edges (from, to, cost).
//   dist   — output vector; pre-sized to |V|.
//   V      — number of vertices.
//   start  — source vertex (0-indexed).
//
// Returns:
//   true  if no negative cycle is reachable from start.
//   false if a negative cycle is detected (some dist values are unreliable).
//
// Algorithm:
//   1. Set dist[start] = 0, all others = INFL.
//   2. Repeat V-1 times: for each edge (u, v, w), try to relax dist[v].
//      After V-1 rounds, all shortest paths (if no negative cycle) are found
//      because any shortest path has at most V-1 edges.
//   3. Do one more round (the V-th). If any edge can still be relaxed,
//      a negative cycle exists.
bool bellman_ford(const vector<Edge> &edges, vector<ll> &dist, int V, int start) {
    dist[start] = 0;

    // Relax all edges V-1 times.
    for (int i = 0; i < V - 1; i++) {
        for (const auto &e : edges) {
            // Only relax if the source vertex is reachable.
            if (dist[e.from] == INFL) continue;
            if (dist[e.from] + e.cost < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.cost;
            }
        }
    }

    // V-th iteration: check for negative cycles.
    // If any relaxation is still possible, a negative cycle exists.
    for (const auto &e : edges) {
        if (dist[e.from] == INFL) continue;
        if (dist[e.from] + e.cost < dist[e.to]) {
            return false;  // Negative cycle detected.
        }
    }

    return true;  // No negative cycle.
}

// --- Minimal usage example ---
// Input: N M start, then M lines of (u v cost) for directed edges.
int main() {
    int N, M, start;
    cin >> N >> M >> start;

    vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        cin >> edges[i].from >> edges[i].to >> edges[i].cost;
    }

    vector<ll> dist(N, INFL);
    bool no_neg_cycle = bellman_ford(edges, dist, N, start);

    if (!no_neg_cycle) {
        cout << "NEGATIVE CYCLE" << endl;
    } else {
        for (int i = 0; i < N; i++) {
            if (dist[i] == INFL)
                cout << "INF" << endl;
            else
                cout << dist[i] << endl;
        }
    }

    return 0;
}
