#include <bits/stdc++.h>
using namespace std;

// ======================================== //

int main()
{
    int N, K;
    cin >> N >> K;

    int years = 0, sum = 0;
    while (sum < K)
    {
        sum += N + years;
        years++;
    }

    cout << years - 1 << endl;

    return 0;
}