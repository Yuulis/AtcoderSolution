// Prim's Algorithm — Minimum Spanning Tree using priority_queue.
//
// Builds a Minimum Spanning Tree by greedily expanding from a starting vertex,
// always picking the cheapest edge that connects a visited vertex to an
// unvisited vertex.
//
// Time:  O((V + E) log V)  — using a binary heap.
// Space: O(V + E)          — adjacency list + priority queue.
//
// Typical AtCoder use cases:
//   - Same as Kruskal: minimum cost to connect all nodes.
//   - Prim is sometimes preferred for dense graphs (E close to V^2).
//
// Caveats:
//   - Assumes the graph is connected for a spanning tree to exist.
//   - For sparse graphs, Kruskal with DSU is often simpler.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int to;
    ll cost;
};

template <class T>
using Graph = vector<vector<T>>;

// prim: compute the total weight of the MST starting from vertex 0.
//
// Parameters:
//   graph — adjacency list of Edge (to, cost).
//   V     — number of vertices.
//
// Returns:
//   Total weight of the MST.
//
// Algorithm:
//   1. Start from vertex 0, mark it as visited.
//   2. Push all edges from vertex 0 into a min-heap (priority queue).
//   3. Extract the cheapest edge (cost, to) from the heap.
//      a. If `to` is already visited, skip it.
//      b. Otherwise, mark `to` as visited, add cost to total,
//         and push all edges from `to` into the heap.
//   4. Repeat until all vertices are visited.
ll prim(const Graph<Edge> &graph, int V) {
    vector<bool> visited(V, false);
    using P = pair<ll, int>;  // (cost, vertex)
    priority_queue<P, vector<P>, greater<P>> pq;

    visited[0] = true;
    for (const auto &e : graph[0]) {
        pq.emplace(e.cost, e.to);
    }

    ll total = 0;
    while (!pq.empty()) {
        auto [c, v] = pq.top();
        pq.pop();

        if (visited[v]) continue;
        visited[v] = true;
        total += c;

        for (const auto &e : graph[v]) {
            if (!visited[e.to]) {
                pq.emplace(e.cost, e.to);
            }
        }
    }

    return total;
}

// --- Minimal usage example ---
// Input: N M, then M lines of (u v cost) for undirected edges.
int main() {
    int N, M;
    cin >> N >> M;

    Graph<Edge> G(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        ll cost;
        cin >> u >> v >> cost;
        G[u].push_back({v, cost});
        G[v].push_back({u, cost});
    }

    ll ans = prim(G, N);
    cout << ans << endl;

    return 0;
}
