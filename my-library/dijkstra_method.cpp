#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr auto INF = 1e+9;

struct Edge
{
    ll to;
    ll cost;
};

using Graph = vector<vector<Edge>>;
using Pair = pair<ll, ll>; // { distance, from }

// ダイクストラ法(基本実装)
// distances は頂点数と同じサイズ, 全要素 INF で初期化しておく
void Dijkstra(const Graph &graph, vector<ll> &distances, ll startIndex)
{
    // 「現時点での最短距離, 頂点」の順に取り出す priority_queue
    // デフォルトの priority_queue は降順に取り出すため greater を使う
    priority_queue<Pair, vector<Pair>, greater<Pair>> p_queue;
    p_queue.emplace((distances[startIndex] = 0), startIndex);

    while (!p_queue.empty())
    {
        const ll distance = p_queue.top().first;
        const ll from = p_queue.top().second;
        p_queue.pop();

        // 最短距離でなければ処理しない
        if (distances[from] < distance)
            continue;

        // 現在の頂点からの各辺について
        for (const auto &edge : graph[from])
        {
            // to までの新しい距離
            const ll d = (distances[from] + edge.cost);

            // d が現在の記録より小さければ更新
            if (d < distances[edge.to])
                p_queue.emplace((distances[edge.to] = d), edge.to);
        }
    }
}

// ref : https://zenn.dev/reputeless/books/standard-cpp-for-competitive-programming/viewer/dijkstra