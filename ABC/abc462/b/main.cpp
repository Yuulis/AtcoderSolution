#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N;
    cin >> N;

    vector<vector<int>> ans(N);
    rep(i, 0, N) {
        int K;
        cin >> K;
        rep(j, 0, K) {
            int A;
            cin >> A;
            ans[A - 1].push_back(i + 1);
        }
    }

    rep(i, 0, N) {
        cout << ans[i].size();
        for (auto a : ans[i])
            cout << " " << a;
        cout << endl;
    }

    return 0;
}