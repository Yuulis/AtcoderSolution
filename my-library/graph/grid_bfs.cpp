// Grid BFS — BFS on a 2D grid ('.'/'#'), 4-direction movement, shortest distance.
//
// A very common pattern in AtCoder: given an H x W grid where '.' is a
// passable cell and '#' is a wall, find the shortest distance from a start
// cell to a goal cell (or to all cells).
//
// BFS on a grid is essentially BFS on a graph where:
//   - Each cell (i, j) is a "vertex".
//   - Each cell has up to 4 neighbors (up, down, left, right).
//   - An edge exists between adjacent cells if both are passable ('.').
//
// Since all moves have equal cost (1 step), BFS guarantees shortest paths.
//
// Time:  O(H * W)   — each cell is visited at most once.
// Space: O(H * W)   — for the distance array and queue.
//
// Typical AtCoder use cases:
//   - Shortest path on a grid (e.g., maze, map navigation).
//   - Reachability on a grid.
//   - Multi-source BFS (start from multiple cells simultaneously).
//   - Extremely common in ABC C/D problems.
//
// Caveats:
//   - Check grid boundaries carefully to avoid out-of-bounds access.
//   - The direction arrays (dx, dy) define the 4 cardinal directions.
//   - For 8-direction movement, add diagonal entries to dx/dy.
//   - For 0-indexed grids, start/goal coordinates should be 0-indexed.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int INF = 1e9;

// 4-direction movement vectors: up, down, left, right.
// dx[i] is the row offset, dy[i] is the column offset.
//
//   direction 0: (-1,  0) → up    (row decreases)
//   direction 1: ( 1,  0) → down  (row increases)
//   direction 2: ( 0, -1) → left  (column decreases)
//   direction 3: ( 0,  1) → right (column increases)
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

// grid_bfs: compute shortest distances from (sx, sy) on a 2D grid.
//
// Parameters:
//   grid — H x W grid of characters. '.' = passable, '#' = wall.
//   dist — output H x W array of distances. Pre-filled with INF.
//   H, W — grid dimensions.
//   sx, sy — start cell (0-indexed row and column).
//
// After execution, dist[i][j] = shortest distance from (sx, sy) to (i, j),
// or INF if (i, j) is unreachable.
//
// Algorithm (identical to graph BFS, adapted for 2D coordinates):
//   1. Set dist[sx][sy] = 0, push (sx, sy) into the queue.
//   2. Pop (x, y) from the front of the queue.
//   3. For each of the 4 directions:
//      a. Compute the next cell (nx, ny) = (x + dx[d], y + dy[d]).
//      b. Check bounds: 0 <= nx < H and 0 <= ny < W.
//      c. Check passability: grid[nx][ny] != '#'.
//      d. Check if unvisited: dist[nx][ny] == INF.
//      e. If all checks pass, set dist[nx][ny] = dist[x][y] + 1 and enqueue.
//   4. Repeat until the queue is empty.
void grid_bfs(const vector<string> &grid, vector<vector<int>> &dist,
              int H, int W, int sx, int sy) {
    // FIFO queue of (row, col) pairs.
    queue<pair<int, int>> que;

    // Start cell: distance is 0.
    dist[sx][sy] = 0;
    que.push({sx, sy});

    while (!que.empty()) {
        // Pop the front cell. Its distance is already finalized.
        auto [x, y] = que.front();
        que.pop();

        // Try all 4 directions.
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            // Boundary check: make sure (nx, ny) is inside the grid.
            // This is CRITICAL — forgetting this causes out-of-bounds access.
            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;

            // Wall check: cannot pass through '#'.
            if (grid[nx][ny] == '#') continue;

            // Already visited check: skip if we already know a shorter path.
            if (dist[nx][ny] != INF) continue;

            // All checks passed — update distance and enqueue.
            dist[nx][ny] = dist[x][y] + 1;
            que.push({nx, ny});
        }
    }
}

// --- Minimal usage example ---
// Input:
//   H W
//   sx sy gx gy   (0-indexed start and goal coordinates)
//   grid[0]        (string of length W, e.g., "..#..")
//   grid[1]
//   ...
//   grid[H-1]
//
// Output: shortest distance from (sx, sy) to (gx, gy), or -1 if unreachable.
int main() {
    int H, W;
    cin >> H >> W;

    int sx, sy, gx, gy;
    cin >> sx >> sy >> gx >> gy;

    vector<string> grid(H);
    for (int i = 0; i < H; i++) {
        cin >> grid[i];
    }

    // Initialize distance array with INF (meaning "unvisited").
    vector<vector<int>> dist(H, vector<int>(W, INF));

    // Run BFS from the start cell.
    grid_bfs(grid, dist, H, W, sx, sy);

    // Output the shortest distance to the goal.
    if (dist[gx][gy] == INF)
        cout << -1 << endl;   // Goal is unreachable.
    else
        cout << dist[gx][gy] << endl;

    return 0;
}
