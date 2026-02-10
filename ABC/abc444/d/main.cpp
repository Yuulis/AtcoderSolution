#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using ll = long long;

// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    rep(i, 0, N) cin >> A[i];

    const int MAX = 200200;

    vector<int> imos(MAX, 0);
    rep(i, 0, N)
    {
        imos[0]++;
        imos[A[i]]--;
    }

    vector<int> ans;
    ll ps = 0;
    ll carry_out = 0;
    rep(i, 0, MAX)
    {
        ps += imos[i];

        ll sum = ps + carry_out;
        ans.push_back(sum % 10);
        carry_out = sum / 10;
    }

    while (!ans.empty() && ans.back() == 0)
    {
        ans.pop_back();
    }

    reverse(all(ans));
    for (auto &&d : ans)
    {
        cout << d;
    }
    cout << endl;

    return 0;
}