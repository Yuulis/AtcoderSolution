/*
 * Weighted (Potential) Union-Find
 *
 * Each node x holds a "potential" value pot[x]. The invariant maintained is:
 *   pot[y] - pot[x] = w   after calling unite(x, y, w).
 *
 * Internally, each tree stores relative weights from child to parent.
 * weight(x) gives the potential of x relative to its root, i.e.
 *   pot[x] - pot[root(x)] = weight(x).
 * Therefore:
 *   pot[y] - pot[x] = weight(y) - weight(x)   (when x and y share the same root).
 *
 * Operations:
 *   same(x, y)       — true if x and y belong to the same component.
 *   unite(x, y, w)   — merge so that pot[y] - pot[x] = w.
 *                       Returns false if they are already connected and
 *                       the constraint is contradictory.
 *   diff(x, y)       — returns pot[y] - pot[x] (undefined if not connected).
 *
 * Time:  O(alpha(n)) amortized per operation (path compression + union by size).
 * Space: O(n).
 *
 * Typical use cases:
 *   - Problems where edges encode difference constraints (e.g. "A - B = w").
 *   - ABC 087 D, ABC 280 E, and similar "potential / weight" UF problems.
 *
 * Caveats:
 *   - diff(x, y) is meaningful only when same(x, y) is true.
 *   - Weight type T must support +, -, and unary - (use ll for most cases).
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
struct WeightedUnionFind {
    vector<int> par, sz;
    vector<T> wt; // wt[x] = potential of x relative to its parent

    WeightedUnionFind(int n) : par(n), sz(n, 1), wt(n, 0) {
        iota(par.begin(), par.end(), 0);
    }

    // Find root of x with path compression.
    // After this call, wt[x] stores the potential of x relative to its root.
    int root(int x) {
        if (par[x] == x) return x;
        int r = root(par[x]);
        wt[x] += wt[par[x]]; // accumulate weight along the path
        par[x] = r;
        return r;
    }

    // Potential of x relative to its root: pot[x] - pot[root(x)].
    T weight(int x) {
        root(x); // ensure path is compressed so wt[x] is up to date
        return wt[x];
    }

    // Check if x and y are in the same component.
    bool same(int x, int y) {
        return root(x) == root(y);
    }

    // Merge components so that pot[y] - pot[x] = w.
    // Returns false if x and y are already connected with a different weight.
    bool unite(int x, int y, T w) {
        // We want: pot[y] - pot[x] = w
        // In terms of root weights: (pot[y] - pot[ry]) - (pot[x] - pot[rx]) + (pot[ry] - pot[rx]) = w
        // => new edge weight from ry to rx: w - weight(y) + weight(x)
        T wy = weight(y), wx = weight(x);
        int rx = root(x), ry = root(y);
        if (rx == ry) {
            // Already connected — check consistency
            return (wy - wx) == w;
        }
        // Union by size: attach smaller tree under larger tree
        // We set par[ry] = rx, so wt[ry] = pot[ry] - pot[rx]
        // pot[y] - pot[x] = w  =>  (wy + pot[ry]) - (wx + pot[rx]) = w
        // =>  pot[ry] - pot[rx] = w + wx - wy
        T edge_w = w + wx - wy;
        if (sz[rx] < sz[ry]) {
            swap(rx, ry);
            edge_w = -edge_w;
        }
        par[ry] = rx;
        wt[ry] = edge_w;
        sz[rx] += sz[ry];
        return true;
    }

    // Returns pot[y] - pot[x].  Only valid when same(x, y) is true.
    T diff(int x, int y) {
        return weight(y) - weight(x);
    }
};

int main() {
    // Example: N nodes, Q queries
    // Query format:
    //   0 x y w  — unite x and y with pot[y] - pot[x] = w
    //   1 x y    — print pot[y] - pot[x], or "?" if not connected
    int N, Q;
    cin >> N >> Q;

    WeightedUnionFind<ll> wuf(N);

    while (Q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int x, y;
            ll w;
            cin >> x >> y >> w;
            if (!wuf.unite(x, y, w)) {
                // Contradiction — the given weight conflicts with existing data
                cout << "CONTRADICTION" << endl;
            }
        } else {
            int x, y;
            cin >> x >> y;
            if (wuf.same(x, y)) {
                cout << wuf.diff(x, y) << endl;
            } else {
                cout << "?" << endl;
            }
        }
    }
    return 0;
}
