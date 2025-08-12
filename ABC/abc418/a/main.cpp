#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    int N;
    string S;
    cin >> N >> S;

    if (N < 3)
    {
        cout << "No" << endl;
        return 0;
    }

    if (S.substr(N - 3) == "tea")
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}