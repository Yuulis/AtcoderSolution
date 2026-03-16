#include <bits/stdc++.h>
using namespace std;

#define fix(x) fixed << setprecision(x)

constexpr auto PI = 3.14159265358979;

// ======================================== //

int main()
{
    int D;
    cin >> D;

    cout << fix(10) << (double)PI * D * D / 4 << endl;

    return 0;
}