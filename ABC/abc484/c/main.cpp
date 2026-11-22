#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)


// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) cin >> B[i];

    int l = 0, r = N - 1;
    while (l < N && A[l] == B[l])
        l++;

    if (l == N)
    {
        cout << "Yes" << endl;
        return 0;
    }

    while (r >= 0 && A[r] == B[r])
        r--;

    bool right = (A[l] == B[r]);
    rep(i, l, r)
    {
        if (A[i + 1] != B[i])
        {
            right = false;
            break;
        }
    }

    bool left = (A[r] == B[l]);
    rep(i, l + 1, r + 1)
    {
        if (A[i - 1] != B[i])
        {
            left = false;
            break;
        }
    }

    if (left || right)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}