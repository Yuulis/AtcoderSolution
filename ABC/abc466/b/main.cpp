#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<set<int>> colors(M);
    rep(i, 0, N) {
        int C, S;
        cin >> C >> S;
        colors[C - 1].insert(S);
    }

    rep(k, 0, M) {
        if (colors[k].size() == 0) {
            cout << -1 << endl;
        }
        else {
            cout << *colors[k].rbegin() << endl;
        }
    }

    return 0;
}