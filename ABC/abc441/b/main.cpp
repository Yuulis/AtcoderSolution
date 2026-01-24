#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    string S, T;
    cin >> S >> T;

    map<char, int> mp;
    rep(i, 0, N)
    {
        mp[S[i]] = 1;
    }
    rep(i, 0, M)
    {
        if (mp[T[i]] == 1)
            mp[T[i]] = 0;
        else
            mp[T[i]] = -1;
    }

    int Q;
    cin >> Q;

    while (Q--)
    {
        string w;
        cin >> w;

        bool flag = false;
        for (auto &&c : w)
        {
            if (mp[c] == 1)
            {
                cout << "Takahashi" << endl;
                flag = true;
                break;
            }
            else if (mp[c] == -1)
            {
                cout << "Aoki" << endl;
                flag = true;
                break;
            }
        }

        if (!flag)
            cout << "Unknown" << endl;
    }

    return 0;
}