/*
 * 2D Cumulative Sum (2D Prefix Sum)
 *
 * Given an H x W grid of values, precompute a prefix-sum table so that
 * the sum of any axis-aligned rectangle can be answered in O(1).
 *
 * Build (inclusion-exclusion on the prefix table):
 *   ps[i+1][j+1] = grid[i][j]
 *                 + ps[i][j+1] + ps[i+1][j]
 *                 - ps[i][j]
 *
 *   Here ps is (H+1) x (W+1) with a border of zeros, so that the
 *   formula works uniformly without special-casing row/column 0.
 *
 * Query — sum over the rectangle [r1, r2) x [c1, c2)  (0-indexed, half-open):
 *   sum = ps[r2][c2] - ps[r1][c2] - ps[r2][c1] + ps[r1][c1]
 *
 *   Visually (the four corners of the inclusion-exclusion):
 *
 *       c1        c2
 *   r1  +---------(-)
 *       |  query  |
 *   r2  (-)-------(+)
 *
 *   (+) means add, (-) means subtract.
 *
 * Time:  O(H * W) build, O(1) per query.
 * Space: O(H * W).
 *
 * Typical use cases:
 *   - Rectangle sum queries on a static 2D grid (extremely common in ABC).
 *   - Combined with coordinate compression for sparse grids.
 *   - Sub-routine for 2D imos method verification.
 *
 * Caveats:
 *   - Does NOT support updates.  Rebuild if the grid changes.
 *   - Query range is half-open: rows [r1, r2), columns [c1, c2).
 *   - Use ll if values or sums can overflow int.
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct CumulativeSum2D {
    vector<vector<ll>> ps;

    CumulativeSum2D() {}

    // Build from an H x W grid.
    // After construction, query(r1, c1, r2, c2) is available.
    CumulativeSum2D(const vector<vector<ll>>& grid) {
        int H = (int)grid.size();
        int W = (int)grid[0].size();
        ps.assign(H + 1, vector<ll>(W + 1, 0));

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                ps[i + 1][j + 1] = grid[i][j]
                                  + ps[i][j + 1]
                                  + ps[i + 1][j]
                                  - ps[i][j];
            }
        }
    }

    // Sum over the rectangle [r1, r2) x [c1, c2) (0-indexed, half-open).
    ll query(int r1, int c1, int r2, int c2) const {
        return ps[r2][c2] - ps[r1][c2] - ps[r2][c1] + ps[r1][c1];
    }
};

int main() {
    // Example: read an H x W grid, then answer Q rectangle-sum queries.
    int H, W, Q;
    cin >> H >> W >> Q;

    vector<vector<ll>> grid(H, vector<ll>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];
        }
    }

    CumulativeSum2D cs(grid);

    while (Q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2; // 0-indexed, half-open [r1,r2) x [c1,c2)
        cout << cs.query(r1, c1, r2, c2) << "\n";
    }
    return 0;
}
