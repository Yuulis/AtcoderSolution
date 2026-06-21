// Kruskal's Algorithm — Minimum Spanning Tree using atcoder::dsu.
//
// Builds a Minimum Spanning Tree (MST) of an undirected weighted graph by
// greedily adding the cheapest edge that does not form a cycle.
//
// Time:  O(E log E)  — dominated by sorting edges.
// Space: O(V + E)    — DSU + edge list.
//
// Typical AtCoder use cases:
//   - Minimum cost to connect all cities / nodes.
//   - MST-based problems (e.g., second-best MST, MST + queries).
//
// Caveats:
//   - Assumes the graph is connected for a spanning tree to exist.
//     If not connected, the result is a minimum spanning forest.
//   - Uses atcoder::dsu (ACL) for efficient union-find.

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using ll = long long;

struct Edge {
    int u, v;
    ll cost;
    bool operator<(const Edge &o) const { return cost < o.cost; }
};

// kruskal: compute the total weight of the MST.
//
// Parameters:
//   edges — list of all edges (u, v, cost). Will be sorted in-place.
//   V     — number of vertices.
//
// Returns:
//   Total weight of the MST. If the graph is disconnected, returns the total
//   weight of the minimum spanning forest.
//
// Algorithm:
//   1. Sort all edges by weight in ascending order.
//   2. Initialize a DSU (Disjoint Set Union / Union-Find) with V elements.
//   3. For each edge in sorted order:
//      a. If u and v are in different components, merge them and add the edge
//         to the MST.
//      b. If u and v are already in the same component, skip (adding this edge
//         would create a cycle).
ll kruskal(vector<Edge> &edges, int V) {
    sort(edges.begin(), edges.end());
    atcoder::dsu uf(V);
    ll total = 0;

    for (const auto &e : edges) {
        if (!uf.same(e.u, e.v)) {
            uf.merge(e.u, e.v);
            total += e.cost;
        }
    }

    return total;
}

// --- Minimal usage example ---
// Input: N M, then M lines of (u v cost) for undirected edges.
int main() {
    int N, M;
    cin >> N >> M;

    vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
    }

    ll ans = kruskal(edges, N);
    cout << ans << endl;

    return 0;
}
