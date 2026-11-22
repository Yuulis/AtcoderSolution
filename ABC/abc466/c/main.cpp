#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

template <typename T>
inline bool chmax(T& a, T b) { return ((a < b) ? (a = b, true) : (false)); }

// ======================================== //

bool query(int i, int j) {
    cout << "? " << i << " " << j << endl;
    cout << flush;

    string res;
    cin >> res;

    return res == "Yes";
}

int main()
{
    int N;
    cin >> N;

    int ans = 0;
    int right = 1;
    rep(left, 1, N + 1) {
        chmax(right, left);

        while (right + 1 <= N) {
            if (query(left, right + 1)) {
                right++;
            }
            else {
                break;
            }
        }

        ans += right - left;
    }

    cout << "! " << ans << endl;
    cout << flush;

    return 0;
}