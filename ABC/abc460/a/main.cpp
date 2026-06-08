#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;

    int ans = 0;
    while (M > 0)
    {
        int x = N % M;
        M = x;
        ans++;
    }

    cout << ans << endl;

    return 0;
}