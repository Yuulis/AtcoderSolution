#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, M;
    string S, T;
    cin >> N >> M >> S >> T;

    vector<int> imos(N + 1, 0);
    rep(i, 0, M)
    {
        int L, R;
        cin >> L >> R;
        L--, R--;
        imos[L]++;
        imos[R + 1]--;
    }

    vector<int> ps(N + 1, 0);
    rep(i, 0, N) ps[i + 1] = ps[i] + imos[i];

    rep(i, 0, N)
    {
        if (ps[i + 1] % 2 == 1)
        {
            swap(S[i], T[i]);
        }
    }

    cout << S << endl;

    return 0;
}