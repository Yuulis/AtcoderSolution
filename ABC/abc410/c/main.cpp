#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N, Q;
    cin >> N >> Q;

    vector<int> A(N);
    iota(all(A), 1);

    ll left_shift = 0;

    while (Q--)
    {
        int t;
        cin >> t;

        if (t == 1)
        {
            int p, x;
            cin >> p >> x;
            p--;

            A[(p + left_shift) % N] = x;
        }
        else if (t == 2)
        {
            int p;
            cin >> p;
            p--;

            cout << A[(p + left_shift) % N] << endl;
        }
        else if (t == 3)
        {
            int k;
            cin >> k;

            left_shift += k;
        }
    }

    return 0;
}