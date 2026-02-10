#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, K;
    cin >> N >> K;

    auto digit_sum = [&](int x) -> int
    {
        int res = 0;
        while (x > 0)
        {
            res += x % 10;
            x /= 10;
        }
        return res;
    };

    int ans = 0;
    rep(x, 1, N + 1)
    {
        if (digit_sum(x) == K)
            ans++;
    }

    cout << ans << endl;

    return 0;
}