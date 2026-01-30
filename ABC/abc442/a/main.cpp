#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    string S;
    cin >> S;

    int ans = 0;
    rep(i, 0, S.size())
    {
        if (S[i] == 'i' || S[i] == 'j')
            ans++;
    }

    cout << ans << endl;
    return 0;
}