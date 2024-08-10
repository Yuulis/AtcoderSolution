#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <functional>

template <class T>
using Graph = std::vector<std::vector<T>>;
using Pair_edge = std::pair<long long, int>;

constexpr long long INFL = 1LL << 60;

template <typename T>
inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false)); }

struct Edge
{
    int to;
    long long cost;
};

// Solve the shortest path problem from the start point in the graph.
void Dijkstra(const Graph<Edge> &graph, std::vector<long long> &dist, const int start)
{
    std::priority_queue<Pair_edge, std::vector<Pair_edge>, std::greater<Pair_edge>> que;
    que.emplace((dist[start] = 0), start);

    while (!que.empty())
    {
        const long long distance = que.top().first;
        const int from = que.top().second;
        que.pop();

        if (dist[from] < distance)
            continue;

        for (const auto &edge : graph[from])
        {
            if (chmin(dist[edge.to], dist[from] + edge.cost))
            {
                que.emplace(dist[edge.to], edge.to);
            }
        }
    }
}

int main()
{
    int N, M, start;
    std::cin >> N >> M >> start;

    Graph<Edge> G(N);
    for (int i = 0; i < M; ++i)
    {
        int u, v;
        long long cost;
        std::cin >> u >> v >> cost;
        G[u].push_back({v, cost});
    }

    std::vector<long long> dist(N, INFL);
    Dijkstra(G, dist, start);

    for (int i = 0; i < N; ++i)
    {
        if (dist[i] == INFL)
            std::cout << "INF" << std::endl;
        else
            std::cout << dist[i] << std::endl;
    }
}