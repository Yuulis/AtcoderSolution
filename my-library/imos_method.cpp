#include <bits/stdc++.h>

#define rep(i, start, end) for (int i = (start); i < (int)(end); i++)

using namespace std;

// ======================================== //

int main()
{
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
}