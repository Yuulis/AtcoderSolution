#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

constexpr long long INFL = 1e+18;

using ll = long long;

template <typename T>
inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false)); }

// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<ll> X(N);
    rep(i, 0, N) cin >> X[i];

    set<ll> st;
    st.insert(0);

    auto get_d = [&](const auto itr) -> ll
    {
        if (st.size() == 1)
            return 0;

        ll res = INFL;
        if (itr != st.begin())
            chmin(res, abs(*itr - *prev(itr)));
        if (next(itr) != st.end())
            chmin(res, abs(*itr - *next(itr)));

        return res;
    };

    ll D = 0;
    rep(i, 0, N)
    {
        auto itr_r = st.lower_bound(X[i]);
        auto itr_l = prev(itr_r);

        ll d_l_old = get_d(itr_l);
        ll d_r_old = 0;
        if (itr_r != st.end())
            d_r_old = get_d(itr_r);

        auto itr_x = st.insert(X[i]).first;
        ll d_x = get_d(itr_x);

        ll d_l_new = get_d(itr_l);
        ll d_r_new = 0;
        if (itr_r != st.end())
            d_r_new = get_d(itr_r);

        D += (d_l_new + d_x + d_r_new) - (d_l_old + d_r_old);

        cout << D << endl;
    }

    return 0;
}