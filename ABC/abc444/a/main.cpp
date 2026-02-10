#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    int N;
    cin >> N;

    string S = to_string(N);

    if (S[0] == S[1] && S[1] == S[2])
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}