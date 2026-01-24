#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;
template <class T>
using Graph = vector<vector<T>>;

// ======================================== //

struct Edge
{
    int to, cost;
};

int main()
{
    int N, M, L, S, T;
    cin >> N >> M >> L >> S >> T;
    Graph<Edge> G(N);
    rep(i, 0, M)
    {
        int U, V, C;
        cin >> U >> V >> C;
        U--, V--;
        G[U].push_back({V, C});
    }

    vector<bool> flag(N, false);
    auto dfs = [&](auto &&self, int now, int l, ll total_cost) -> void
    {
        if (l == L)
        {
            if (S <= total_cost && total_cost <= T)
            {
                flag[now] = true;
            }
            return;
        }

        for (auto &&edge : G[now])
        {
            self(self, edge.to, l + 1, total_cost + edge.cost);
        }
    };

    dfs(dfs, 0, 0, 0);

    rep(i, 0, N)
    {
        if (flag[i])
            cout << i + 1 << ' ';
    }

    return 0;
}