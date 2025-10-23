#include <bits/stdc++.h>
using namespace std;

template <class T1, class T2>
inline auto div_floor(T1 a, T2 b)
{
    if (b < 0)
        a *= -1, b *= -1;
    if (a >= 0)
        return a / b;
    else
        return (a + 1) / b - 1;
}

// ======================================== //

int main()
{
    int S, A, B, X;
    cin >> S >> A >> B >> X;

    int ans = S * A * div_floor(X, A + B);
    int rem = X % (A + B);
    ans += S * min(rem, A);

    cout << ans << endl;

    return 0;
}