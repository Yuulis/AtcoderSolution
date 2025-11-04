#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

template <typename T>
inline bool chmax(T &a, T b) { return ((a < b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];

    vector<int> first_pos(M + 1, -1);
    rep(i, 0, N)
    {
        if (first_pos[A[i]] == -1)
        {
            first_pos[A[i]] = i + 1;
        }
    }

    int m = 0;
    rep(i, 1, M + 1)
    {
        if (first_pos[i] == -1)
        {
            cout << 0 << endl;
            return 0;
        }

        chmax(m, first_pos[i]);
    }

    cout << N - m + 1 << endl;

    return 0;
}