#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    int Q;
    cin >> Q;

    bool is_playing = false;
    int volume = 0;
    while (Q--)
    {
        int A;
        cin >> A;

        if (A == 1)
        {
            volume++;
        }
        else if (A == 2)
        {
            volume = max(volume - 1, 0);
        }
        else if (A == 3)
        {
            is_playing = !is_playing;
        }

        if (is_playing && volume >= 3)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}