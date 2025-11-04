#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

constexpr int INF = 1e+9;

template <class T>
using Graph = vector<vector<T>>;

// ======================================== //

struct State
{
    int start;
    int now;
    int distance;
};

int main()
{
    int N, M;
    cin >> N >> M;
    Graph<int> G(N);
    rep(i, 0, M)
    {
        int U, V;
        cin >> U >> V;
        U--;
        V--;
        G[U].push_back(V);
        G[V].push_back(U);
    }
    string S;
    cin >> S;

    vector<vector<int>> from(N, vector<int>(2, -1));
    vector<vector<int>> dist(N, vector<int>(2, INF));

    queue<State> que;
    rep(i, 0, N)
    {
        if (S[i] == 'S')
        {
            from[i][0] = i;
            dist[i][0] = 0;
            que.push({i, i, 0});
        }
    }

    while (!que.empty())
    {
        State state = que.front();
        que.pop();

        for (int next : G[state.now])
        {
            if (from[next][0] == -1)
            {
                from[next][0] = state.start;
                dist[next][0] = state.distance + 1;
                que.push({state.start, next, state.distance + 1});
            }
            else if (from[next][0] != state.start && from[next][1] == -1)
            {
                from[next][1] = state.start;
                dist[next][1] = state.distance + 1;
                que.push({state.start, next, state.distance + 1});
            }
        }
    }

    rep(i, 0, N)
    {
        if (S[i] == 'D')
            cout << dist[i][0] + dist[i][1] << endl;
    }

    return 0;
}