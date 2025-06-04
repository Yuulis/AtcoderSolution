#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N;
    cin >> N;

    set<int> st;
    rep(i, 0, N)
    {
        int A;
        cin >> A;
        st.insert(A);
    }

    cout << st.size() << endl;
    for (auto &&x : st)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}