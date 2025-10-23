#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    int Q;
    cin >> Q;

    stack<int> A, B;
    A.push(0);
    B.push(0);

    while (Q--)
    {
        int t;
        cin >> t;

        if (t == 1)
        {
            char c;
            cin >> c;

            A.push(A.top() + (c == '(' ? 1 : -1));
            B.push(min(B.top(), A.top()));
        }
        else if (t == 2)
        {
            A.pop();
            B.pop();
        }

        if (A.top() == 0 && B.top() >= 0)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}