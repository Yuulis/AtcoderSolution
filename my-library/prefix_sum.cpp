#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (int i = (start); i < (int)(end); i++)

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(N, 0);
    rep(i, 0, N) cin >> A[i];
    vector<vector<int>> B(N, vector<int>(N, 0));
    rep(i, 0, N) rep(j, 0, N) cin >> B[i][j];
    vector<vector<vector<int>>> C(N, vector<vector<int>>(N, vector<int>(N, 0)));
    rep(i, 0, N) rep(j, 0, N) rep(k, 0, N) cin >> C[i][j][k];

    // When given in a closed interval, subtract 1 from the left end.

    // ===== 1-dimension ===== //
    vector<int> ps(N + 1, 0);
    rep(i, 0, N) ps[i + 1] = ps[i] + A[i];

    // sum of [x1, x2)
    int x1, x2;
    cout << ps[x2] - ps[x1] << endl;

    // ===== 2-dimension ===== //
    vector<vector<int>> ps2d(N + 1, vector<int>(N + 1, 0));
    rep(i, 0, N) rep(j, 0, N) ps2d[i + 1][j + 1] = ps2d[i][j + 1] + ps2d[i + 1][j] - ps2d[i][j] + B[i][j];

    // sum of [x1, y1) * [x2, y2)
    int y1, y2;
    cout << ps2d[x2][y2] - ps2d[x1][y2] - ps2d[x2][y1] + ps2d[x1][y1] << endl;

    // ===== 3-dimension ===== //
    vector<vector<vector<int>>> ps3d(N + 1, vector<vector<int>>(N + 1, vector<int>(N + 1, 0)));
    rep(i, 0, N) rep(j, 0, N) rep(k, 0, N) ps3d[i + 1][j + 1][k + 1] = ps3d[i][j + 1][k + 1] + ps3d[i + 1][j][k + 1] + ps3d[i + 1][j + 1][k] - ps3d[i][j][k + 1] - ps3d[i][j + 1][k] - ps3d[i + 1][j][k] + ps3d[i][j][k] + C[i][j][k];

    // sum of [x1, y1, z1) * [x2, y2, z2)
    int z1, z2;
    cout << ps3d[x2][y2][z2] - ps3d[x1][y2][z2] - ps3d[x2][y1][z2] - ps3d[x2][y2][z1] + ps3d[x1][y1][z2] + ps3d[x1][y2][z1] + ps3d[x2][y1][z1] - ps3d[x1][y1][z1] << endl;
}