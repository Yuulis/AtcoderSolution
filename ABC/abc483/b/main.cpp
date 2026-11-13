#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> K(Q);
    rep(i, 0, Q) cin >> K[i];

    vector<int> cards(N);
    iota(all(cards), 1);

    rep(i, 0, Q)
    {
        reverse(cards.begin(), cards.begin() + K[i]);
        rep(j, 0, K[i]) cards[j] *= -1;
    }

    rep(i, 0, N) cout << cards[i] << endl;

    return 0;
}