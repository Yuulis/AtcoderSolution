#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N;
    ll D;
    cin >> N >> D;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];

    ll ans = 0;
    set<ll> st;
    int R = 0;
    rep(L, 0, N)
    {
        while (R < N)
        {
            auto itr = st.lower_bound(A[R]);

            if (itr != st.end() && abs(*itr - A[R]) < D)
                break;
            if (itr != st.begin() && abs(*prev(itr) - A[R]) < D)
                break;

            st.insert(A[R]);
            R++;
        }

        ans += R - L;

        st.erase(A[L]);
    }

    cout << ans << endl;

    return 0;
}