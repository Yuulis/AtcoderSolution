#include <bits/stdc++.h>
using namespace std;

template <class T1, class T2>
inline auto div_ceil(T1 a, T2 b)
{
    if (b < 0)
        a *= -1, b *= -1;
    if (a <= 0)
        return a / b;
    else
        return (a - 1) / b + 1;
}

// ======================================== //

int main()
{
    int N, M;
    cin >> N >> M;

    if (div_ceil(N, 2) >= M)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}