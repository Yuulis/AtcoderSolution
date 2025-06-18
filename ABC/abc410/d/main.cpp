#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

template <class T>
using Graph = vector<vector<T>>;

// ======================================== //

struct Edge
{
    int to;
    int weight;
};

int main()
{
    int N, M;
    cin >> N >> M;
    Graph<Edge> G(N);
    rep(i, 0, M)
    {
        int A, B, W;
        cin >> A >> B >> W;
        A--, B--;
        G[A].push_back({B, W});
    }

    vector<vector<bool>> visited(N, vector<bool>((1 << 10), false));
    queue<pair<int, int>> que;
    que.push({0, 0});
    visited[0][0] = true;

    while (!que.empty())
    {
        auto [now, sum] = que.front();
        que.pop();

        for (auto &&edge : G[now])
        {
            int next_v = edge.to;
            int next_sum = sum ^ edge.weight;

            if (!visited[next_v][next_sum])
            {
                visited[next_v][next_sum] = true;
                que.push({next_v, next_sum});
            }
        }
    }

    rep(bit, 0, (1 << 10))
    {
        if (visited[N - 1][bit])
        {
            cout << bit << endl;
            return 0;
        }
    }

    cout << -1 << endl;
    return 0;
}