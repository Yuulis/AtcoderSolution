// Bipartite Check — 2-coloring BFS to test bipartiteness.
//
// A graph is bipartite if and only if it can be 2-colored: every vertex is
// assigned one of two colors such that no edge connects two vertices of the
// same color. Equivalently, a graph is bipartite iff it contains no odd-length
// cycle.
//
// Time:  O(V + E)
// Space: O(V)
//
// Typical AtCoder use cases:
//   - Checking if a graph is bipartite (2-colorable).
//   - Problems involving partitioning vertices into two groups.
//   - Detecting odd cycles.
//
// Caveats:
//   - Handles disconnected graphs (checks each component separately).
//   - The coloring array can be used to retrieve the actual partition.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// is_bipartite: check if the graph is bipartite and compute a 2-coloring.
//
// Parameters:
//   graph — adjacency list (undirected graph).
//   color — output vector; color[v] will be 0 or 1 for each vertex.
//           Pre-sized to |V|, initialized to -1 (uncolored).
//
// Returns:
//   true if the graph is bipartite, false otherwise.
//
// Algorithm:
//   For each unvisited vertex (to handle disconnected components):
//   1. Assign it color 0 and push it into a BFS queue.
//   2. For each neighbor: if uncolored, assign the opposite color and enqueue.
//      If already colored the same as the current vertex, the graph is NOT
//      bipartite (we found an odd cycle).
bool is_bipartite(const vector<vector<int>> &graph, vector<int> &color) {
    int n = (int)graph.size();
    fill(color.begin(), color.end(), -1);

    for (int s = 0; s < n; s++) {
        if (color[s] != -1) continue;  // Already colored in a previous component.

        // BFS from vertex s.
        queue<int> que;
        color[s] = 0;
        que.push(s);

        while (!que.empty()) {
            int v = que.front();
            que.pop();

            for (int nv : graph[v]) {
                if (color[nv] == -1) {
                    // Assign the opposite color.
                    color[nv] = 1 - color[v];
                    que.push(nv);
                } else if (color[nv] == color[v]) {
                    // Same color on both ends of an edge → not bipartite.
                    return false;
                }
            }
        }
    }

    return true;
}

// --- Minimal usage example ---
// Input: N M, then M lines of (u v) for undirected edges.
int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> color(N, -1);
    if (is_bipartite(graph, color)) {
        cout << "YES (bipartite)" << endl;
        for (int i = 0; i < N; i++) {
            cout << "vertex " << i << ": color " << color[i] << endl;
        }
    } else {
        cout << "NO (not bipartite)" << endl;
    }

    return 0;
}
