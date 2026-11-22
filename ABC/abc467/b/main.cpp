#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N;
    cin >> N;

    int X = 10000, Y = 10000;
    rep(i, 0, N) {
        int A, B;
        string S;
        cin >> A >> B >> S;

        if (S == "keep") {
            X -= B;
        }
        else {
            X -= A;
        }

        Y -= A;
    }

    cout << Y - X << endl;

    return 0;
}