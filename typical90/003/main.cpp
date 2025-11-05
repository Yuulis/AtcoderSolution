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

        auto bfs = [&](int start) -> void
        {
            queue<int> que;
            que.push(start);
            res[start] = 0;
            while (!que.empty())
            {
                int now = que.front();
                que.pop();

                for (auto next : G[now])
                {
                    if (res[next] != -1)
                        continue;

                    res[next] = res[now] + 1;
                    que.push(next);
                }
            }
            return;
        };

        bfs(start);
        return res;
    };

    auto get_farthest = [&](const vector<int> &dist) -> int
    {
        int res = -1;
        int max_dist = -1;
        rep(i, 0, N)
        {
            if (chmax(max_dist, dist[i]))
            {
                res = i;
            }
        }

        return res;
    };

    vector<int> dist_0 = get_dist(0);
    int u = get_farthest(dist_0);

    vector<int> dist_u = get_dist(u);
    int v = get_farthest(dist_u);

    cout << dist_u[v] + 1 << endl;

    return 0;
}