#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define rrep(i, start, end) for (auto i = (start); (i) >= (end); (i)--)

// ======================================== //

struct Edge
{
    int from;
    int to;
    int cost;
};

int main()
{
    int N, M;
    cin >> N >> M;
    vector<Edge> edges(M);
    rep(i, 0, M)
    {
        cin >> edges[i].from >> edges[i].to >> edges[i].cost;
        edges[i].from--;
        edges[i].to--;
    }

    int ans = (1LL << 30) - 1;
    rrep(bit, 29, 0)
    {
        if (ans & (1LL << bit))
        {
            int temp = ans & ~(1 << bit);
            dsu dsu(N);
            for (auto &&e : edges)
            {
                if ((e.cost | temp) == temp)
                {
                    dsu.merge(e.from, e.to);
                }
            }

            if (dsu.same(0, N - 1))
            {
                ans = temp;
            }
        }
    }

    cout << ans << endl;

    return 0;
}