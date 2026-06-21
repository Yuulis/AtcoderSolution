// BFS (Breadth-First Search) on an unweighted graph.
//
// Computes single-source shortest distances on an unweighted graph.
// BFS explores vertices level by level: it visits all vertices at distance d
// before any vertex at distance d+1. This guarantees shortest paths because
// every edge has weight 1.
//
// Time:  O(V + E)   — each vertex and edge is processed exactly once.
// Space: O(V)       — for the distance array and BFS queue.
//
// Typical AtCoder use cases:
//   - Shortest path on unweighted graphs (ABC-level graph problems).
//   - Reachability check from a source vertex.
//   - Connected component exploration.
//
// Caveats:
//   - Only correct for unweighted (or unit-weight) graphs.
//   - For weighted graphs, use Dijkstra or Bellman-Ford instead.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll INFL = 1LL << 60;

// bfs: compute shortest distances from vertex `start` on an unweighted graph.
//
// Parameters:
//   graph  — adjacency list where graph[u] contains the neighbors of u.
//   dist   — output vector; dist[v] will hold the shortest distance from start
//            to v, or INFL if v is unreachable. Must be pre-sized to |V|.
//   start  — the source vertex (0-indexed).
//
// How BFS works step by step:
//   1. Initialize dist[start] = 0 and push start into a FIFO queue.
//   2. Pop the front vertex u from the queue.
//   3. For each neighbor v of u:
//      a. If dist[v] is still INFL (i.e., v has not been visited),
//         set dist[v] = dist[u] + 1 and push v into the queue.
//   4. Repeat steps 2-3 until the queue is empty.
//
// Why a queue (FIFO)?
//   Because a queue processes vertices in the order they were discovered,
//   which means vertices at distance d are all processed before distance d+1.
//   This is what guarantees BFS finds shortest paths on unweighted graphs.
void bfs(const vector<vector<int>> &graph, vector<ll> &dist, int start) {
    // Use a standard FIFO queue. The queue stores vertex indices.
    queue<int> que;

    // Distance from start to itself is 0.
    dist[start] = 0;
    que.push(start);

    while (!que.empty()) {
        // Dequeue the front vertex — this vertex's shortest distance is finalized.
        int v = que.front();
        que.pop();

        // Examine every neighbor of v.
        for (int nv : graph[v]) {
            // If this neighbor has already been visited, skip it.
            // A visited vertex already has its shortest distance set.
            if (dist[nv] != INFL) continue;

            // This is the first time we reach nv, so dist[v] + 1 is optimal.
            dist[nv] = dist[v] + 1;
            que.push(nv);
        }
    }
}

// --- Minimal usage example ---
// Input format:
//   N M start
//   u1 v1
//   u2 v2
//   ...
// where N = number of vertices, M = number of edges (undirected),
// start = source vertex (0-indexed).
int main() {
    int N, M, start;
    cin >> N >> M >> start;

    // Build adjacency list. graph[u] stores all neighbors of vertex u.
    vector<vector<int>> graph(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        // Undirected edge: add both directions.
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Initialize all distances to INFL (meaning "not yet visited").
    vector<ll> dist(N, INFL);
    bfs(graph, dist, start);

    // Output shortest distance from start to each vertex.
    for (int i = 0; i < N; i++) {
        if (dist[i] == INFL)
            cout << "INF" << endl;
        else
            cout << dist[i] << endl;
    }

    return 0;
}
