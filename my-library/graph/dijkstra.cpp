// Dijkstra's Algorithm — single-source shortest path for non-negative weights.
//
// Finds the shortest path from a single source to all other vertices in a
// graph where all edge weights are non-negative.
//
// Time:  O((V + E) log V)  — using a binary heap (priority_queue).
// Space: O(V + E)          — adjacency list + distance array.
//
// Typical AtCoder use cases:
//   - Shortest path in road networks, grid graphs with varying costs.
//   - Problems that ask for minimum cost to reach a destination.
//   - Often combined with reverse graph or multi-source Dijkstra.
//
// Caveats:
//   - Does NOT work with negative edge weights (use Bellman-Ford instead).
//   - Uses a lazy deletion approach: stale entries in the priority queue are
//     skipped via the `if (dist[from] < d) continue;` check.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll INFL = 1LL << 60;

template <class T>
inline bool chmin(T &a, T b) { return (a > b) ? (a = b, true) : false; }

struct Edge {
    int to;
    ll cost;
};

template <class T>
using Graph = vector<vector<T>>;

// dijkstra: compute shortest distances from `start` on a weighted graph.
//
// Parameters:
//   graph  — adjacency list of Edge (to, cost). Costs must be >= 0.
//   dist   — output vector; pre-sized to |V|, will hold shortest distances.
//   start  — source vertex (0-indexed).
void dijkstra(const Graph<Edge> &graph, vector<ll> &dist, int start) {
    // Min-heap of (distance, vertex). We always extract the vertex with
    // the smallest tentative distance.
    using P = pair<ll, int>;
    priority_queue<P, vector<P>, greater<P>> pq;

    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, from] = pq.top();
        pq.pop();

        // Lazy deletion: if we already found a shorter path to `from`, skip.
        if (dist[from] < d) continue;

        for (const auto &e : graph[from]) {
            if (chmin(dist[e.to], dist[from] + e.cost)) {
                pq.emplace(dist[e.to], e.to);
            }
        }
    }
}

// --- Minimal usage example ---
// Input: N M start, then M lines of (u v cost) for directed edges.
int main() {
    int N, M, start;
    cin >> N >> M >> start;

    Graph<Edge> G(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        ll cost;
        cin >> u >> v >> cost;
        G[u].push_back({v, cost});
    }

    vector<ll> dist(N, INFL);
    dijkstra(G, dist, start);

    for (int i = 0; i < N; i++) {
        if (dist[i] == INFL)
            cout << "INF" << endl;
        else
            cout << dist[i] << endl;
    }

    return 0;
}
