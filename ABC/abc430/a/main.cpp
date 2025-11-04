#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    int A, B, C, D;
    cin >> A >> B >> C >> D;

    if (C >= A && B > D)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}