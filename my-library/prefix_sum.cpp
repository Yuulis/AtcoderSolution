#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (int i = (start); i < (int)(end); i++)

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];
    vector<vector<int>> B(N, vector<int>(M));
    rep(i, 0, N) rep(j, 0, M) cin >> B[i][j];

    // 1-dimension
    vector<int> ps(N + 1, 0);
    rep(i, 0, N) ps[i + 1] = ps[i] + A[i];

    // sum of [3, 8)
    cout << ps[8] - ps[3] << endl;

    // 2-dimension
    vector<vector<int>> ps2d(N + 1, vector<int>(M + 1, 0));
    rep(i, 0, N) rep(j, 0, M) ps2d[i + 1][j + 1] = ps2d[i + 1][j] + ps2d[i][j + 1] - ps2d[i][j] + B[i][j];

    rep(i, 0, N) rep(j, 0, M) ps2d[i + 1][j + 1] = ps2d[i + 1][j] + B[i][j];
    rep(i, 0, N) rep(j, 0, M) ps2d[i + 1][j + 1] = ps2d[i][j + 1] + ps2d[i + 1][j + 1];

    // sum of [2, 5) * [4, 7)
    cout << ps2d[8][7] - ps2d[2][7] - ps2d[5][4] + ps2d[2][4] << endl;
}