#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

using mint = static_modint<1000000000>;

int main()
{
    int N, K;
    cin >> N >> K;

    vector<mint> A(N + 1), S(N + 1);
    rep(i, 0, min(K, N + 1))
    {
        A[i] = 1;
        S[i] = A[i];
        if (i >= 1)
        {
            S[i] += S[i - 1];
        }
    }

    rep(i, K, N + 1)
    {
        A[i] = S[i - 1];
        if (i - K >= 1)
        {
            A[i] -= S[i - K - 1];
        }

        S[i] = S[i - 1] + A[i];
    }

    cout << A[N].val() << endl;

    return 0;
}