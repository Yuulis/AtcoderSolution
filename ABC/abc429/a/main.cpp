#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;

    rep(i, 1, N + 1)
    {
        if (i <= M)
            cout << "OK" << endl;
        else
            cout << "Too Many Requests" << endl;
    }

    return 0;
}