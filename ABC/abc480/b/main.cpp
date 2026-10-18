#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    rep(i, 0, N) cin >> S[i];

    vector<int> cnt(N, 0);
    rep(i, 0, M) {
        string T;
        cin >> T;

        int cand = 0, near = 0, exact = -1;
        rep(j, 0, N) {
            if (S[j] == T) {
                exact = j;
                break;
            }

            if (S[j].size() != T.size()) continue;

            int mismatch = 0;
            rep(k, 0, S[j].size()) {
                if (S[j][k] != T[k]) {
                    mismatch++;
                    if (mismatch >= 2) break;
                }
            }

            if (mismatch == 1) {
                cand++;
                near = j;
            }
        }

        if (exact != -1) cnt[exact]++;
        else if (cand == 1) cnt[near]++;
    }

    rep(i, 0, N) cout << cnt[i] << endl;

    return 0;
}