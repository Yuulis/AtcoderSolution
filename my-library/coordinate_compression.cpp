#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A.at(i);

    vector<int> B = A;

    sort(B.begin(), B.end());

    B.erase(unique(B.begin(), B.end()), B.end());

    vector<int> ans(N);
    for (int i = 0; i < N; i++)
    {
        ans.at(i) = lower_bound(B.begin(), B.end(), A.at(i)) - B.begin();
    }

    for (auto i : ans)
        cout << i << endl;
}