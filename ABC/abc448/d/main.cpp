#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

template <class T>
using Graph = vector<vector<T>>;

// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];
    Graph<int> G(N);
    rep(i, 0, N - 1)
    {
        int U, V;
        cin >> U >> V;
        U--, V--;
        G[U].push_back(V);
        G[V].push_back(U);
    }

    map<int, int> mp;
    vector<bool> ans(N, false);
    int cnt = 0;

    auto dfs = [&](auto self, int now, int parent) -> void
    {
        if (mp[A[now]] == 1)
            cnt++;
        mp[A[now]]++;

        if (cnt > 0)
            ans[now] = true;
        else
            ans[now] = false;

        for (auto &&next : G[now])
        {
            if (next == parent)
                continue;
            self(self, next, now);
        }

        mp[A[now]]--;
        if (mp[A[now]] == 1)
            cnt--;
    };

    dfs(dfs, 0, -1);

    rep(i, 0, N)
    {
        if (ans[i])
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}