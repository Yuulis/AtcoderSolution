#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N, T;
    cin >> N >> T;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];

    int ans = 0, last_open_time = 0;
    bool is_open = true;
    rep(i, 0, N)
    {
        if (is_open)
        {
            ans += A[i] - last_open_time;
            is_open = false;
        }

        int next_open_time = A[i] + 100;

        if (next_open_time < T)
        {
            while (i + 1 < N && A[i + 1] < next_open_time)
            {
                i++;
            }

            last_open_time = next_open_time;
            is_open = true;
        }
        else
        {
            last_open_time = T;
            is_open = false;
        }
    }

    if (is_open && last_open_time < T)
    {
        ans += T - last_open_time;
    }

    cout << ans << endl;
    return 0;
}