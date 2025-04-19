#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
template <class T>
using Graph = vector<vector<T>>;

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    Graph<int> G(N);
    rep(i, 0, M)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dsu uf_1(N), uf_2(N);
    rep(k, 0, N)
    {
        for (auto &&v : G[k])
        {
            if (v < k)
                uf_1.merge(k, v);
            else
                uf_2.merge(k, v);
        }

        if (uf_1.size(0) == k + 1)
            cout << uf_2.size(0) - (k + 1) << endl;
        else
            cout << -1 << endl;
    }

    return 0;
}