#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    string S;
    cin >> S;

    int cnt_a = 0, cnt_ab = 0;
    int ans = 0;
    for (auto &&c : S)
    {
        if (c == 'A')
        {
            cnt_a++;
        }
        else if (c == 'B')
        {
            if (cnt_a > 0)
            {
                cnt_a--;
                cnt_ab++;
            }
        }
        else if (c == 'C')
        {
            if (cnt_ab > 0)
            {
                cnt_ab--;
                ans++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}