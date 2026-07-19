#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(N - 1);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N - 1) cin >> B[i];

    auto calc = [&](int bit) -> int {
        int res = 0;
        int now = bit;
        rep(i, 0, N) {
            if (now != A[i]) {
                res++;
            }

            if (i < N - 1) {
                now ^= B[i];
            }
        }
        return res;
        };

    cout << min(calc(0), calc(1)) << endl;

    return 0;
}