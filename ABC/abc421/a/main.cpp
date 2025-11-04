#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<string> S(N);
    rep(i, 0, N) cin >> S[i];
    int X;
    string Y;
    cin >> X >> Y;

    if (S[X - 1] == Y)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}