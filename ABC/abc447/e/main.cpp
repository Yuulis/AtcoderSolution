#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define rrep(i, start, end) for (auto i = (start); (i) >= (end); (i)--)

using mint = modint998244353;
using Pair_int = pair<int, int>;

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<Pair_int> edges(M);
    rep(i, 0, M)
    {
        int U, V;
        cin >> U >> V;
        U--, V--;
        edges[i] = {U, V};
    }

    dsu uf(N);
    int cnt = N;
    rrep(i, M - 1, 0)
    {
        if (cnt <= 2)
            break;

        if (!uf.same(edges[i].first, edges[i].second))
        {
            uf.merge(edges[i].first, edges[i].second);
            cnt--;
        }
    }

    mint ans = 0;
    mint pow2 = 2;
    rep(i, 0, M)
    {
        if (!uf.same(edges[i].first, edges[i].second))
        {
            ans += pow2;
        }
        pow2 *= 2;
    }

    cout << ans.val() << endl;

    return 0;
}