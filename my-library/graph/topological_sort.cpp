// Topological Sort — Kahn's algorithm (in-degree based BFS).
//
// Produces a linear ordering of vertices in a DAG (Directed Acyclic Graph)
// such that for every directed edge u -> v, u appears before v.
//
// Time:  O(V + E)
// Space: O(V + E)
//
// Typical AtCoder use cases:
//   - Task scheduling with dependencies.
//   - DP on DAGs (process vertices in topological order).
//   - Detecting if a directed graph has a cycle.
//
// Caveats:
//   - Only defined for DAGs. If the graph has a cycle, not all vertices can
//     be included in the topological order; this implementation detects cycles
//     by checking if the result size equals V.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// topological_sort: return a topological ordering of vertices, or an empty
// vector if a cycle is detected.
//
// Parameters:
//   graph  — adjacency list of a directed graph.
//   V      — number of vertices.
//
// Algorithm (Kahn's):
//   1. Compute in-degree for each vertex.
//   2. Push all vertices with in-degree 0 into a queue.
//   3. While the queue is not empty:
//      a. Pop vertex u, append it to the result.
//      b. For each neighbor v of u, decrement in-degree of v.
//         If in-degree of v becomes 0, push v into the queue.
//   4. If result size < V, there is a cycle.
vector<int> topological_sort(const vector<vector<int>> &graph, int V) {
    vector<int> indeg(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : graph[u]) {
            indeg[v]++;
        }
    }

    queue<int> que;
    for (int i = 0; i < V; i++) {
        if (indeg[i] == 0) que.push(i);
    }

    vector<int> order;
    order.reserve(V);

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        order.push_back(u);

        for (int v : graph[u]) {
            indeg[v]--;
            if (indeg[v] == 0) que.push(v);
        }
    }

    // If not all vertices are in the order, a cycle exists.
    if ((int)order.size() != V) return {};

    return order;
}

// --- Minimal usage example ---
// Input: N M, then M lines of (u v) for directed edges.
int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    vector<int> order = topological_sort(graph, N);

    if (order.empty()) {
        cout << "CYCLE DETECTED" << endl;
    } else {
        for (int i = 0; i < (int)order.size(); i++) {
            if (i > 0) cout << " ";
            cout << order[i];
        }
        cout << endl;
    }

    return 0;
}
