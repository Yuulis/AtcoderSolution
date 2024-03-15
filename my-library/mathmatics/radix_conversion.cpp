#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define rep(i, start, end) for (ll i = (start); i < (ll)(end); i++)

int main()
{
    // decimal -> binary (filled with eight 0s)
    unsigned x = 0;
    cout << static_cast<std::bitset<8>>(x) << endl;

    // Example
    cout << static_cast<std::bitset<8>>(10) << endl; // 00001010
}

// k-base num -> decimal
int ktoDec(ll x, ll k)
{
    ll res = 0;
    ll base = 1;
    while (x > 0)
    {
        res = res + (x % 10) * base;
        x = x / 10;
        base = base * k;
    }

    return res;
}
// Example
int x = ktoDec(101, 4); // x = 17

// decimal -> k-base num
int dectoK(ll x, ll k)
{
    string s;
    while (x != 0)
    {
        s += to_string(x % k);
        x /= k;
    }

    int res = atoi(s.c_str());
    return res;
}
// Example
int x = dectoK(10, 4); // x = 22

// decimal -> hexadecimal (specifiable length)
string dectoh(int x, int size = 0)
{
    char hex_buf[16];
    sprintf(hex_buf, "%X", x);
    string hex_str = hex_buf;
    if (size == 0)
    {
        return hex_str;
    }

    string front;
    if (x >= 0)
        front = "0";
    else
        front = "F";

    int diff = size - hex_str.length();
    rep(i, 0, diff) hex_str = front + hex_str;

    if (diff < 0)
        hex_str.erase(0, -diff);

    return hex_str;
}
// Example
string s = dectoh(26, 3); // s = "01A"