#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, S;
    cin >> N >> S;
    vector<int> T(N + 1, 0);
    rep(i, 1, N + 1) cin >> T[i];

    rep(i, 1, N + 1)
    {
        if (T[i] - T[i - 1] > S)
        {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}