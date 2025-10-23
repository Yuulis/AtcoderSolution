#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

template <class T>
using Graph = vector<vector<T>>;

template <typename T>
inline bool chmax(T &a, T b) { return ((a < b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N;
    cin >> N;
    Graph<int> G(N);
    rep(i, 0, N - 1)
    {
        int A, B;
        cin >> A >> B;
        A--, B--;
        G[A].push_back(B);
        G[B].push_back(A);
    }

    auto get_dist = [&](int start) -> vector<int>
    {
        vector<int> res(N, -1);

        auto dfs = [&](auto &self, int now, int parent, int d) -> void
        {
            res[now] = d;
            for (auto next : G[now])
            {
                if (next == parent)
                    continue;

                self(self, next, now, d + 1);
            }
            return;
        };

        dfs(dfs, start, -1, 0);
        return res;
    };

    auto get_farthest = [&](const vector<int> &dist) -> int
    {
        int res = -1;
        int max_dist = -1;
        rep(i, 0, N)
        {
            if (dist[i] > max_dist)
            {
                res = i;
                max_dist = dist[i];
            }
            else if (dist[i] == max_dist)
            {
                chmax(res, i);
            }
        }

        return res;
    };

    vector<int> dist_0 = get_dist(0);
    int u = get_farthest(dist_0);

    vector<int> dist_u = get_dist(u);
    int w = get_farthest(dist_u);

    vector<int> dist_w = get_dist(w);

    rep(v, 0, N)
    {
        int from_u = dist_u[v];
        int from_w = dist_w[v];

        if (from_u == from_w)
        {
            cout << max(u, w) + 1 << endl;
        }
        else if (from_u < from_w)
        {
            cout << w + 1 << endl;
        }
        else
        {
            cout << u + 1 << endl;
        }
    }

    return 0;
}