#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    string S, T;
    cin >> S >> T;

    vector<int> s_a_cnts, t_a_cnts;
    string s_no_a, t_no_a;
    int cnt_s = 0, cnt_t = 0;
    for (char c : S)
    {
        if (c == 'A')
        {
            cnt_s++;
        }
        else
        {
            s_no_a += c;
            s_a_cnts.push_back(cnt_s);
            cnt_s = 0;
        }
    }
    s_a_cnts.push_back(cnt_s);

    for (char c : T)
    {
        if (c == 'A')
        {
            cnt_t++;
        }
        else
        {
            t_no_a += c;
            t_a_cnts.push_back(cnt_t);
            cnt_t = 0;
        }
    }
    t_a_cnts.push_back(cnt_t);

    if (s_no_a != t_no_a)
    {
        cout << -1 << endl;
        return 0;
    }

    int ans = 0;
    rep(i, 0, s_a_cnts.size())
    {
        ans += abs(s_a_cnts[i] - t_a_cnts[i]);
    }

    cout << ans << endl;

    return 0;
}