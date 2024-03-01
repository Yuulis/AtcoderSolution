#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    unsigned x = 0;
    cout << static_cast<std::bitset<8>>(x) << endl; // decimal -> binary (filled with eight 0s)
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
    for (int i = 0; i < diff; i++)
    {
        hex_str = front + hex_str;
    }

    if (diff < 0)
    {
        hex_str.erase(0, -diff);
    }
    return hex_str;
}