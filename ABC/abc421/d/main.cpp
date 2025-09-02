#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    ll Rt, Ct, Ra, Ca;
    cin >> Rt >> Ct >> Ra >> Ca;
    ll N;
    int M, L;
    cin >> N >> M >> L;
    vector<pair<char, ll>> T(M), A(L);
    rep(i, 0, M) cin >> T[i].first >> T[i].second;
    rep(i, 0, L) cin >> A[i].first >> A[i].second;

    map<char, pair<int, int>> dir = {
        {'U', {-1, 0}},
        {'D', {1, 0}},
        {'L', {0, -1}},
        {'R', {0, 1}}};

    ll ans = 0;
    int T_idx = 0, A_idx = 0;
    int rest_T = T[0].second, rest_A = A[0].second;
    while (T_idx < M && A_idx < L)
    {
        ll s = min(rest_T, rest_A);
        ll Rta = Rt - Ra, Cta = Ct - Ca;
        pair<ll, ll> dt = dir[T[T_idx].first], da = dir[A[A_idx].first];
        ll dRta = dt.first - da.first, dCta = dt.second - da.second;

        if (dRta == 0 && dCta == 0)
        {
            if (Rta == 0 && Cta == 0)
                ans += s;
        }
        else
        {
            ll k = -1;
            if (dRta == 0)
            {
                if (Rta == 0 && Cta % dCta == 0)
                    k = -Cta / dCta;
            }
            else if (dCta == 0)
            {
                if (Cta == 0 && Rta % dRta == 0)
                    k = -Rta / dRta;
            }
            else
            {
                if (Rta % dRta == 0 && Cta % dCta == 0)
                {
                    if (-Rta / dRta == -Cta / dCta)
                        k = -Rta / dRta;
                }
            }

            if (1 <= k && k <= s)
                ans++;
        }

        Rt += s * dt.first;
        Ct += s * dt.second;
        Ra += s * da.first;
        Ca += s * da.second;

        rest_T -= s, rest_A -= s;
        if (rest_T == 0)
        {
            T_idx++;
            if (T_idx < M)
                rest_T = T[T_idx].second;
        }
        if (rest_A == 0)
        {
            A_idx++;
            if (A_idx < L)
                rest_A = A[A_idx].second;
        }
    }

    cout << ans << endl;

    return 0;
}