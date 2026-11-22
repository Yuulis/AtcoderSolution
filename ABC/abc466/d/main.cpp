#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> R(M), C(M);
    vector<int> time_row(N, -1), time_col(N, -1);
    rep(i, 0, M) {
        cin >> R[i] >> C[i];
        R[i]--;
        C[i]--;

        time_row[R[i]] = i;
        time_col[C[i]] = i;
    }

    int ans = 0;
    rep(i, 0, M) {
        if (time_row[R[i]] == i && time_col[C[i]] == i)
            ans++;
    }

    cout << ans << endl;

    return 0;
}