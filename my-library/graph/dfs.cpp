// DFS (Depth-First Search) — recursive and iterative (stack) versions.
//
// DFS explores as far as possible along each branch before backtracking.
// Unlike BFS which goes level by level, DFS dives deep into the graph first.
//
// This file provides two implementations:
//   1. Recursive DFS  — simple and natural, but may stack-overflow on deep graphs.
//   2. Iterative DFS  — uses an explicit stack, safe for large graphs (up to ~10^6 nodes).
//
// Both versions record the preorder visitation order (the order in which
// vertices are first discovered).
//
// Time:  O(V + E)   — each vertex and edge is processed exactly once.
// Space: O(V)       — for the visited array and recursion/stack.
//
// Typical AtCoder use cases:
//   - Reachability / connectivity checks.
//   - Preorder / postorder traversals on trees.
//   - Detecting connected components.
//   - Foundation for cycle detection, topological sort, etc.
//
// Caveats:
//   - Recursive DFS may cause stack overflow for V > ~10^5 depending on system.
//     Use iterative version for safety in competitive programming.
//   - DFS does NOT find shortest paths (use BFS for that).

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// --- Recursive DFS ---
//
// How recursive DFS works:
//   1. Mark the current vertex as visited.
//   2. Record it in the preorder list (we just discovered it).
//   3. For each unvisited neighbor, recursively call DFS on it.
//   4. When all neighbors are explored, the function returns (backtracks).
//
// The recursion naturally uses the call stack as the "stack" data structure.
// This makes the code very clean, but the recursion depth equals the longest
// path in the DFS tree, which can be O(V) in the worst case.
void dfs_recursive(const vector<vector<int>> &graph, vector<bool> &visited,
                   vector<int> &preorder, int v) {
    // Mark vertex v as visited so we never process it again.
    visited[v] = true;

    // Record v in preorder — this is the moment we "discover" v.
    preorder.push_back(v);

    // Explore each neighbor of v.
    for (int nv : graph[v]) {
        // Only visit unvisited neighbors to avoid infinite loops.
        if (!visited[nv]) {
            dfs_recursive(graph, visited, preorder, nv);
        }
    }
    // (Implicit backtrack: when this function returns, we go back to the caller.)
}

// --- Iterative DFS (using explicit stack) ---
//
// How iterative DFS works:
//   1. Push the start vertex onto a stack.
//   2. Pop the top vertex from the stack.
//   3. If it is already visited, skip it.
//   4. Otherwise mark it as visited, record it in preorder.
//   5. Push all its unvisited neighbors onto the stack.
//   6. Repeat until the stack is empty.
//
// Note: The visitation order may differ slightly from recursive DFS because
// the stack processes neighbors in reverse order (LIFO). To match the exact
// recursive order, push neighbors in reverse.
void dfs_iterative(const vector<vector<int>> &graph, vector<bool> &visited,
                   vector<int> &preorder, int start) {
    // Explicit stack replaces the call stack.
    stack<int> stk;
    stk.push(start);

    while (!stk.empty()) {
        int v = stk.top();
        stk.pop();

        // Skip if already visited (a vertex may be pushed multiple times).
        if (visited[v]) continue;

        // Mark as visited and record in preorder.
        visited[v] = true;
        preorder.push_back(v);

        // Push neighbors in reverse order so that the smallest-index neighbor
        // is processed first (matching the typical recursive DFS order).
        for (int i = (int)graph[v].size() - 1; i >= 0; i--) {
            int nv = graph[v][i];
            if (!visited[nv]) {
                stk.push(nv);
            }
        }
    }
}

// --- Minimal usage example ---
// Input format:
//   N M start
//   u1 v1
//   u2 v2
//   ...
// Demonstrates both recursive and iterative DFS and prints preorder.
int main() {
    int N, M, start;
    cin >> N >> M >> start;

    vector<vector<int>> graph(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Sort adjacency lists so both versions visit neighbors in the same order.
    for (auto &adj : graph) sort(adj.begin(), adj.end());

    // --- Recursive DFS ---
    {
        vector<bool> visited(N, false);
        vector<int> preorder;
        dfs_recursive(graph, visited, preorder, start);
        cout << "Recursive DFS preorder:";
        for (int v : preorder) cout << " " << v;
        cout << endl;
    }

    // --- Iterative DFS ---
    {
        vector<bool> visited(N, false);
        vector<int> preorder;
        dfs_iterative(graph, visited, preorder, start);
        cout << "Iterative DFS preorder:";
        for (int v : preorder) cout << " " << v;
        cout << endl;
    }

    return 0;
}
