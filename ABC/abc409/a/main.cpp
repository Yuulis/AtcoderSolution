#include <bits/stdc++.h>

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using namespace std;

// ======================================== //

int main()
{
    int N;
    string T, A;
    cin >> N >> T >> A;

    rep(i, 0, N)
    {
        if (T[i] == 'o' && A[i] == 'o')
        {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;
    return 0;
}
