#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];

    int sum = 0;
    rep(i, 0, N) sum += A[i];

    rep(i, 0, N)
    {
        if (sum - A[i] == M)
        {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;

    return 0;
}