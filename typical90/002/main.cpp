#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define rrep(i, start, end) for (auto i = (start); (i) >= (end); (i)--)

// ======================================== //

int main()
{
    int N;
    cin >> N;

    rep(bit, 0, (1 << N))
    {
        string s;
        rrep(i, N - 1, 0)
        {
            if (!(bit & (1 << i)))
                s += "(";
            else
                s += ")";
        }

        int cnt = 0;
        bool flag = true;
        for (auto &&c : s)
        {
            if (c == '(')
                cnt++;
            else
                cnt--;

            if (cnt < 0)
            {
                flag = false;
                break;
            }
        }

        if (cnt == 0 && flag)
            cout << s << endl;
    }
}