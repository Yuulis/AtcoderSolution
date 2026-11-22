#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    int N, M, T;
    cin >> N >> M >> T;

    int now = N, time = 0;
    while (M--)
    {
        int A, B;
        cin >> A >> B;

        now -= A - time;
        time = A;
        if (now <= 0) {
            cout << "No" << endl;
            return 0;
        }

        now = min(N, now + (B - A));
        time = B;
    }

    now -= T - time;
    time = T;
    if (now <= 0) {
        cout << "No" << endl;
        return 0;
    }

    cout << "Yes" << endl;

    return 0;
}