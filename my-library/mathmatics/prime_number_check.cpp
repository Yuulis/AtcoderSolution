#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool isPrime(ll x)
{
    if (x < 2)
        return false;
    else
        for (ll i = 2; i * i <= x; i++)
            if (x % i == 0)
                return false;

    return true;
}