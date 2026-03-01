#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline bool chmax(T &a, T b) { return ((a < b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    string S;
    cin >> S;

    map<char, int> mp;
    for (auto c : S)
        mp[c]++;

    int max_cnt = 0;
    for (auto [_, cnt] : mp)
        chmax(max_cnt, cnt);

    string ans;
    for (auto c : S)
    {
        if (mp[c] != max_cnt)
            ans += c;
    }

    cout << ans << endl;

    return 0;
}