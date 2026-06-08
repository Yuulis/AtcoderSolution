#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(M);
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, M) cin >> B[i];

    sort(all(A));
    sort(all(B));

    int i = 0, ans = 0;
    rep(j, 0, M) {
        while (i < N && !(B[j] <= 2 * A[i])) i++;

        if (i < N) {
            ans++;
            i++;
        }
        else {
            break;
        }
    }

    cout << ans << endl;

    return 0;
}