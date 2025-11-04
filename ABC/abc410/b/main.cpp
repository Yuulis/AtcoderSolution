#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

constexpr int INF = 1e+9;

template <typename T>
inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> X(Q);
    rep(i, 0, Q) cin >> X[i];

    vector<int> boxes(N + 1, 0);
    rep(i, 0, Q)
    {
        if (X[i] >= 1)
        {
            boxes[X[i]]++;
        }
        else
        {
            int idx = -1, cnt = INF;
            rep(j, 1, N + 1)
            {
                if (chmin(cnt, boxes[j]))
                {
                    idx = j;
                }
            }

            boxes[idx]++;
            X[i] = idx;
        }
    }

    for (auto &&x : X)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}