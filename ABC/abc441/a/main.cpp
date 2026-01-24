#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    int P, Q, X, Y;
    cin >> P >> Q >> X >> Y;

    if ((P <= X && X <= P + 99) && (Q <= Y && Y <= Q + 99))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}