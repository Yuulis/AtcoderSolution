#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (ll i = (start); i < (ll)(end); i++)
using ll = long long;

ll N;
vector<bool> v(N + 1, true);

void sieve()
{
    v[0] = false;
    v[1] = false;
    for (int i = 2; pow(i, 2) <= N; i++)
    {
        if (v[i])
            for (int j = 2; i * j <= N; j++)
                v[i * j] = false;
    }
}

int main()
{
    // Determine prime numbers for integers less than or equal to N.
    // If n is prime, v[n] = true; otherwise, v[n] = false.
    sieve();

    // Example : Output prime numbers from 2 to 9.
    rep(i, 2, 10)
    {
        if (v[i])
            cout << i << endl;
    }
}
