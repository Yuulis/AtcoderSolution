#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

template <typename T>
inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N, X;
    cin >> N >> X;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];

    rep(i, 0, N)
    {
        if (chmin(X, A[i]))
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }

    return 0;
}