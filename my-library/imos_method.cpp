#include <bits/stdc++.h>

#define rep(i, start, end) for (int i = (start); i < (int)(end); i++)

using namespace std;

// ======================================== //

int main()
{
    // 1-dimension
    int N, Q;
    cin >> N >> Q;

    // query
    vector<int> v(N + 1);
    rep(i, 0, Q)
    {
        int L, R;
        cin >> L >> R;

        v[L]++;
        v[R + 1]--;
    }

    // calclate prefix_sum
    vector<int> ps(N + 1, 0);
    rep(i, 0, N) ps[i + 1] = ps[i] + v[i];

    // 2-dimension
    int H, W;
    cin >> H >> W;

    // query
    vector<vector<int>> v2d(H, vector<int>(W, 0));
    rep(i, 0, Q)
    {
        int A, B, C, D;
        cin >> A >> B >> C >> D;

        v2d[A][B]++;
        v2d[A][D + 1]--;
        v2d[C + 1][B]--;
        v2d[C + 1][D + 1]++;
    }

    // calclate prefix_sum
    vector<vector<int>> ps2d(H + 1, vector<int>(W + 1, 0));
    rep(i, 0, H) rep(j, 0, W) ps2d[i + 1][j + 1] = ps2d[i + 1][j] + ps2d[i][j];
    rep(j, 0, W) rep(i, 0, H) ps2d[i + 1][j + 1] = ps2d[i][j + 1] + ps2d[i + 1][j + 1];
}