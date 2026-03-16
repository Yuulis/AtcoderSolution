#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    int H, W, Q;
    cin >> H >> W >> Q;

    while (Q--)
    {
        int t;
        cin >> t;

        if (t == 1)
        {
            int R;
            cin >> R;

            cout << R * W << endl;

            H -= R;
        }
        else
        {
            int C;
            cin >> C;

            cout << C * H << endl;

            W -= C;
        }
    }

    return 0;
}