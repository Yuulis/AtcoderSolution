// Cycle Detection — directed graph (DFS 3-color) and undirected graph.
//
// Two separate functions:
//   1. has_cycle_directed:   detects a cycle in a DIRECTED graph using
//                            the classic 3-color DFS (white/gray/black).
//   2. has_cycle_undirected: detects a cycle in an UNDIRECTED graph using
//                            DFS with parent tracking.
//
// Time:  O(V + E) for both.
// Space: O(V)     for color/visited arrays + recursion stack.
//
// Typical AtCoder use cases:
//   - Checking if a directed graph is a DAG (no cycle → can topological sort).
//   - Detecting cycles in undirected graphs (e.g., is this a tree?).
//
// Caveats:
//   - Directed and undirected cycle detection are DIFFERENT algorithms.
//     In undirected graphs, an edge u-v creates entries in both adj[u] and
//     adj[v], so we must track the parent to avoid false positives.
//   - These implementations detect existence only, not the actual cycle path.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// === Directed graph cycle detection (3-color DFS) ===
//
// Colors:
//   0 (WHITE) — vertex has not been visited.
//   1 (GRAY)  — vertex is currently being processed (on the DFS stack).
//   2 (BLACK) — vertex and all its descendants are fully processed.
//
// A cycle exists if and only if we encounter a GRAY vertex while exploring
// from another GRAY vertex (i.e., a back edge in the DFS tree).

bool dfs_directed(const vector<vector<int>> &graph, vector<int> &color, int v) {
    color[v] = 1;  // Mark as GRAY (currently in DFS stack).

    for (int nv : graph[v]) {
        if (color[nv] == 1) return true;   // Back edge → cycle found.
        if (color[nv] == 0) {              // Unvisited → recurse.
            if (dfs_directed(graph, color, nv)) return true;
        }
        // color[nv] == 2 (BLACK): already fully processed, skip.
    }

    color[v] = 2;  // Mark as BLACK (fully processed).
    return false;
}

bool has_cycle_directed(const vector<vector<int>> &graph) {
    int n = (int)graph.size();
    vector<int> color(n, 0);  // All WHITE initially.

    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            if (dfs_directed(graph, color, i)) return true;
        }
    }
    return false;
}

// === Undirected graph cycle detection (DFS with parent tracking) ===
//
// In an undirected graph, each edge u-v appears in both adj[u] and adj[v].
// When we DFS from u to v, we will see u in adj[v], but that is NOT a cycle
// — it is just the edge we came from. So we track the parent vertex and skip it.
//
// A cycle exists if we encounter an already-visited vertex that is NOT our parent.

bool dfs_undirected(const vector<vector<int>> &graph, vector<bool> &visited,
                    int v, int parent) {
    visited[v] = true;

    for (int nv : graph[v]) {
        if (nv == parent) continue;        // Skip the edge we came from.
        if (visited[nv]) return true;      // Already visited, not parent → cycle.
        if (dfs_undirected(graph, visited, nv, v)) return true;
    }
    return false;
}

bool has_cycle_undirected(const vector<vector<int>> &graph) {
    int n = (int)graph.size();
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs_undirected(graph, visited, i, -1)) return true;
        }
    }
    return false;
}

// --- Minimal usage example ---
// Input:
//   type N M     (type: 0 = directed, 1 = undirected)
//   u1 v1
//   ...
int main() {
    int type, N, M;
    cin >> type >> N >> M;

    vector<vector<int>> graph(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        if (type == 1) graph[v].push_back(u);  // Undirected: add both directions.
    }

    bool has_cycle;
    if (type == 0) {
        has_cycle = has_cycle_directed(graph);
    } else {
        has_cycle = has_cycle_undirected(graph);
    }

    cout << (has_cycle ? "CYCLE DETECTED" : "NO CYCLE") << endl;

    return 0;
}
