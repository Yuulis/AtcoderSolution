// LCA (Lowest Common Ancestor) by binary lifting (doubling).
//
// Preprocesses a rooted tree to answer LCA queries in O(log V) each.
// Also supports computing the depth of each node and the distance between
// any two nodes in the tree.
//
// Preprocessing: O(V log V) time and space.
// Query:         O(log V) per LCA query.
//
// Typical AtCoder use cases:
//   - LCA queries on trees (very common in tree problems).
//   - Distance between two nodes: depth[u] + depth[v] - 2 * depth[lca(u,v)].
//   - Path queries combined with Euler tour or heavy-light decomposition.
//
// Caveats:
//   - Requires the tree to be rooted. Root is typically vertex 0.
//   - LOG should be set to ceil(log2(V)). LOG = 20 covers V up to ~10^6.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct LCA {
    int n, LOG;
    vector<vector<int>> parent;  // parent[k][v] = 2^k-th ancestor of v
    vector<int> depth;

    // Build LCA structure from an adjacency list with given root.
    // graph: undirected tree adjacency list.
    // root:  root vertex (0-indexed).
    LCA(const vector<vector<int>> &graph, int root)
        : n((int)graph.size()), LOG(1) {
        while ((1 << LOG) < n) LOG++;
        parent.assign(LOG, vector<int>(n, -1));
        depth.assign(n, -1);

        // BFS to compute depth and direct parent (parent[0]).
        queue<int> que;
        depth[root] = 0;
        que.push(root);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int nv : graph[v]) {
                if (depth[nv] != -1) continue;
                depth[nv] = depth[v] + 1;
                parent[0][nv] = v;
                que.push(nv);
            }
        }

        // Fill the doubling table: parent[k][v] = parent[k-1][parent[k-1][v]].
        for (int k = 1; k < LOG; k++) {
            for (int v = 0; v < n; v++) {
                if (parent[k - 1][v] == -1)
                    parent[k][v] = -1;
                else
                    parent[k][v] = parent[k - 1][parent[k - 1][v]];
            }
        }
    }

    // Query: find LCA of u and v.
    int query(int u, int v) const {
        // Make u the deeper node.
        if (depth[u] < depth[v]) swap(u, v);

        // Lift u up to the same depth as v.
        int diff = depth[u] - depth[v];
        for (int k = 0; k < LOG; k++) {
            if ((diff >> k) & 1) {
                u = parent[k][u];
            }
        }

        if (u == v) return u;

        // Lift both u and v simultaneously until their parents converge.
        for (int k = LOG - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }

        return parent[0][u];
    }

    // Distance between u and v in the tree.
    int dist(int u, int v) const {
        return depth[u] + depth[v] - 2 * depth[query(u, v)];
    }
};

// --- Minimal usage example ---
// Input:
//   N Q root
//   u1 v1   (N-1 tree edges)
//   ...
//   a1 b1   (Q queries: LCA of a and b)
//   ...
int main() {
    int N, Q, root;
    cin >> N >> Q >> root;

    vector<vector<int>> graph(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    LCA lca(graph, root);

    for (int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        int ancestor = lca.query(a, b);
        cout << "LCA(" << a << ", " << b << ") = " << ancestor
             << "  dist = " << lca.dist(a, b) << endl;
    }

    return 0;
}
