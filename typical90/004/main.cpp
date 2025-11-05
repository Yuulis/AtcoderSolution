#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int H, W;
    cin >> H >> W;
    vector<vector<int>> A(H, vector<int>(W));
    rep(i, 0, H) rep(j, 0, W) cin >> A[i][j];

    vector<int> rows(H), cols(W);
    rep(i, 0, H) rep(j, 0, W)
    {
        rows[i] += A[i][j];
        cols[j] += A[i][j];
    }

    rep(i, 0, H) rep(j, 0, W)
    {
        cout << rows[i] + cols[j] - A[i][j] << ' ';
    }
    cout << endl;
}