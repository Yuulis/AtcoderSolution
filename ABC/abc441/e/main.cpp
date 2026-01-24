#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;

    fenwick_tree<int> fw(2 * N + 1);
    fw.add(0 + N, 1);

    ll ps = 0, ans = 0;
    rep(i, 0, N)
    {
        if (S[i] == 'A')
            ps++;
        else if (S[i] == 'B')
            ps--;

        fw.add(ps + N, 1);
        ans += fw.sum(0, ps + N);
    }

    cout << ans << endl;

    return 0;
}