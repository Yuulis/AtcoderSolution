#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N;
    cin >> N;

    bool is_login = false;
    int ans = 0;

    rep(i, 0, N)
    {
        string S;
        cin >> S;

        if (S == "login")
        {
            is_login = true;
        }
        else if (S == "logout")
        {
            is_login = false;
        }
        else if (S == "private")
        {
            if (!is_login)
            {
                ans++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}