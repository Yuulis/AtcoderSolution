#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    int X, Y, L, R, A, B;
    cin >> X >> Y >> L >> R >> A >> B;

    int time_x = max(0, min(B, R) - max(A, L));
    int time_y = (B - A) - time_x;

    cout << time_x * X + time_y * Y << endl;

    return 0;
}