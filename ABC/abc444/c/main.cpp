#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    sort(all(A));

    set<ll> ans;

    if (A[0] == A[N - 1])
        ans.insert(A[0]);

    for (int m = 2; m <= N; m += 2)
    {
        ll L = A[0] + A[m - 1];
        if (m < N)
        {
            if (A[m] != L || A[N - 1] != L)
                continue;
        }

        bool flag = true;
        rep(i, 1, m / 2)
        {
            if (A[i] + A[m - 1 - i] != L)
            {
                flag = false;
                break;
            }
        }

        if (flag)
            ans.insert(L);
    }

    for (auto &&x : ans)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}