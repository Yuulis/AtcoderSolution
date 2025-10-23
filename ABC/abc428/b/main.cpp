#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

template <typename T>
inline bool chmax(T &a, T b) { return ((a < b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N, K;
    string S;
    cin >> N >> K >> S;

    map<string, int> mp;
    rep(i, 0, N - K + 1)
    {
        mp[S.substr(i, K)]++;
    }

    int ans = 0;
    for (const auto &[key, value] : mp)
    {
        chmax(ans, value);
    }

    cout << ans << endl;

    for (const auto &[key, value] : mp)
    {
        if (value == ans)
        {
            cout << key << " ";
        }
    }
    cout << endl;

    return 0;
}