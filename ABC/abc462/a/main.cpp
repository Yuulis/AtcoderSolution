#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    string S;
    cin >> S;

    for (char c : S)
    {
        if (isdigit(c))
            cout << c;
    }
    cout << endl;

    return 0;
}