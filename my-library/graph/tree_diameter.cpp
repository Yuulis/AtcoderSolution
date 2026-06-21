// Tree Diameter — finding the longest path in a tree via two BFS passes.
//
// The diameter of a tree is the length of the longest path between any two
// vertices. This algorithm finds it in O(V) using two BFS passes.
//
// Time:  O(V)
// Space: O(V)
//
// Typical AtCoder use cases:
//   - Finding the diameter of a tree (very common tree problem).
//   - Finding the farthest vertex from any given vertex.
//   - Problems involving the "center" of a tree.
//
// Caveats:
//   - Only works on trees (connected acyclic graphs).
//   - For weighted trees, use edge weights in BFS (or DFS with weights).
//     This implementation supports weighted edges.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll INFL = 1LL << 60;

struct Edge {
    int to;
    ll cost;
};

// bfs_farthest: find the farthest vertex from `start` and its distance.
//
// Returns: {farthest_vertex, distance_to_it}.
//
// This is a standard BFS on a weighted tree. Since trees have no cycles,
// BFS visits each vertex exactly once and finds the unique path.
pair<int, ll> bfs_farthest(const vector<vector<Edge>> &tree, int start) {
    int n = (int)tree.size();
    vector<ll> dist(n, INFL);
    queue<int> que;
    dist[start] = 0;
    que.push(start);

    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (const auto &e : tree[v]) {
            if (dist[e.to] != INFL) continue;
            dist[e.to] = dist[v] + e.cost;
            que.push(e.to);
        }
    }

    // Find the vertex with maximum distance.
    int farthest = start;
    ll max_dist = 0;
    for (int i = 0; i < n; i++) {
        if (dist[i] != INFL && dist[i] > max_dist) {
            max_dist = dist[i];
            farthest = i;
        }
    }

    return {farthest, max_dist};
}

// tree_diameter: find the diameter of the tree.
//
// Algorithm (two-BFS trick):
//   1. BFS from any vertex (say vertex 0) to find the farthest vertex u.
//   2. BFS from u to find the farthest vertex v. The distance u-v is the diameter.
//
// Why does this work?
//   The farthest vertex from any vertex in a tree is always an endpoint of
//   some diameter path. So BFS #1 finds one endpoint, and BFS #2 finds the
//   other endpoint and the diameter length.
//
// Returns: the diameter (longest path length).
ll tree_diameter(const vector<vector<Edge>> &tree) {
    auto [u, _d1] = bfs_farthest(tree, 0);
    auto [_v, diameter] = bfs_farthest(tree, u);
    return diameter;
}

// --- Minimal usage example ---
// Input: N, then N-1 lines of (u v cost) for undirected tree edges.
int main() {
    int N;
    cin >> N;

    vector<vector<Edge>> tree(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        ll cost;
        cin >> u >> v >> cost;
        tree[u].push_back({v, cost});
        tree[v].push_back({u, cost});
    }

    cout << tree_diameter(tree) << endl;

    return 0;
}
