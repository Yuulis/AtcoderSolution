#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(x) (x).begin(), (x).end()

// cf : https://qiita.com/ganyariya/items/33f1326154b85db465c3
// cf : https://qiita.com/drken/items/97e37dd6143e33a64c8c

vector<ll> a;

// Whether index satisfies the condition
bool check(int index, int key)
{
    if (a[index] >= key)
        return true;
    else
        return false;
}

ll binary_search(ll key)
{
    ll ng = -1;
    ll ok = (int)a.size();

    while (abs(ok - ng) > 1)
    {
        ll mid = (ok + ng) / 2;

        if (check(mid, key))
            ok = mid;
        else
            ng = mid;
    }
    return ok;
}

int main()
{
    int N;
    a.resize(N);

    sort(all(a)); // sorting is essential!
    if (binary_search(a.begin(), a.end(), 5))
    {
        cout << "Found" << endl;
    }

    // Return the smallest iterator of elements in A that is greater than or equal to 6.
    auto itr = lower_bound(all(a), 6);

    // Return the smallest iterator of elements in A that is greater than 6.
    auto itr = upper_bound(all(a), 6);
}