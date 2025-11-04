#include <bits/stdc++.h>

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using namespace std;

using ll = long long;
template <class T>
using Graph = vector<vector<T>>;

// ======================================== //

struct Edge
{
    int to;
    ll cost;
};

int main()
{
    int N;
    cin >> N;
    vector<int> X(N);
    rep(i, 0, N) cin >> X[i];

    Graph<Edge> G(N);
    rep(i, 0, N - 1)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }

    ll ans = 0;

    auto dfs = [&](auto self, int now, int parent) -> ll
    {
        ll charge_sum = X[now];

        for (auto &&e : G[now])
        {
            if (e.to == parent)
                continue;

            ll charge_sum_child = self(self, e.to, now);
            ans += abs(charge_sum_child) * e.cost;
            charge_sum += charge_sum_child;
        }

        return charge_sum;
    };

    dfs(dfs, 0, -1);

    cout << ans << endl;

    return 0;
}
