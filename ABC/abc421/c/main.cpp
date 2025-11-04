#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N;
    string S;
    cin >> N >> S;

    vector<int> pos_A;
    rep(i, 0, 2 * N)
    {
        if (S[i] == 'A')
            pos_A.push_back(i);
    }

    ll cost1 = 0, cost2 = 0;
    rep(i, 0, N)
    {
        cost1 += abs(pos_A[i] - (2 * i));
        cost2 += abs(pos_A[i] - (2 * i + 1));
    }

    cout << min(cost1, cost2) << endl;

    return 0;
}