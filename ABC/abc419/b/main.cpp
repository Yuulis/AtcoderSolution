#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    int Q;
    cin >> Q;

    multiset<int> st;
    while (Q--)
    {
        int t;
        cin >> t;

        if (t == 1)
        {
            int x;
            cin >> x;
            st.insert(x);
        }
        else if (t == 2)
        {
            cout << *st.begin() << endl;
            st.erase(st.begin());
        }
    }

    return 0;
}