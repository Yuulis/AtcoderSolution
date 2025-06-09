#include <bits/stdc++.h>

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using namespace std;

// ======================================== //

string solve()
{
    int N;
    string S;
    cin >> N >> S;

    int l = -1;
    rep(i, 0, N - 1)
    {
        if (S[i] > S[i + 1])
        {
            l = i;
            break;
        }
    }

    if (l == -1)
        return S;

    int r = -1;
    rep(i, l + 1, N)
    {
        if (S[i] > S[l])
        {
            r = i - 1;
            break;
        }
    }

    if (r == -1)
        r = N - 1;

    rotate(S.begin() + l, S.begin() + l + 1, S.begin() + r + 1);
    return S;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        cout << solve() << endl;
    }

    return 0;
}
