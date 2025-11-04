#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    rep(i, 0, N) cin >> S[i];

    set<vector<string>> st;
    rep(i, 0, N - M + 1) rep(j, 0, N - M + 1)
    {
        vector<string> subgrid(M);
        rep(di, 0, M)
        {
            subgrid[di] = S[i + di].substr(j, M);
        }
        st.insert(subgrid);
    }

    cout << st.size() << endl;

    return 0;
}