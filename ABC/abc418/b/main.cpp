#include <bits/stdc++.h>
using namespace std;

#define fix(x) fixed << setprecision(x)
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

template <typename T>
inline bool chmax(T &a, T b) { return ((a < b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    string S;
    cin >> S;

    double ans = 0;
    rep(l, 0, S.size()) rep(r, l + 1, S.size())
    {
        string sub = S.substr(l, r - l + 1);
        if (*sub.begin() == 't' && *sub.rbegin() == 't' && r - l + 1 >= 3)
        {
            int cnt = 0;
            rep(i, l, r + 1)
            {
                if (S[i] == 't')
                    cnt++;
            }

            chmax(ans, (double)(cnt - 2) / (r - l + 1 - 2));
        }
    }

    cout << fix(10) << ans << endl;
}