#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    multiset<int> st;
    rep(i, 0, N) cin >> A[i], st.insert(A[i]);

    while (Q--)
    {
        int K;
        cin >> K;
        vector<int> B(K);
        rep(i, 0, K) cin >> B[i], B[i]--;

        rep(i, 0, K)
        {
            if (st.contains(A[B[i]]))
                st.erase(st.find(A[B[i]]));
        }

        cout << *st.begin() << endl;

        rep(i, 0, K) st.insert(A[B[i]]);
    }

    return 0;
}