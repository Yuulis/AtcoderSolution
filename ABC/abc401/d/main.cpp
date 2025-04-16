#include <bits/stdc++.h>
using namespace std;

#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define fix(x) fixed << setprecision(x)
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define repe(i, start, end) for (auto i = (start); (i) <= (end); (i)++)
#define rrep(i, start, end) for (auto i = (start); (i) >= (end); (i)--)

constexpr auto PI = 3.14159265358979;
constexpr int INF = 1e+9;
constexpr long long INFL = 1e+18;

using ll = long long;
using lld = long double;
// using mint = modint1000000007;
using mint = modint998244353;
using Pair_int = pair<int, int>;
using Pair_ll = pair<ll, ll>;
template <class T>
using Graph = vector<vector<T>>;

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
ll pow_int(ll x, ll n)
{
    ll res = 1;
    while (n > 0)
    {
        if (n & 1)
            res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}
ll pow_mod(ll x, ll n, ll mod)
{
    ll res = 1;
    while (n > 0)
    {
        if (n & 1)
            res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}
ll gcd(ll x, ll y)
{
    if (x < y)
        swap(x, y);
    ll r;
    while (y > 0)
    {
        r = x % y;
        x = y;
        y = r;
    }
    return x;
}
ll lcm(ll x, ll y) { return ll(x / gcd(x, y)) * y; }
ll nCk(ll n, ll r)
{
    if (r < 0 || n < r)
        return 0;
    ll ans = 1;
    for (ll i = 1; i <= r; i++)
    {
        ans *= n--;
        ans /= i;
    }
    return ans;
}
int get_rand(int seed, int min, int max)
{
    static mt19937_64 mt64(seed);
    uniform_int_distribution<int> get_rand_int(min, max);
    return get_rand_int(mt64);
}
template <typename T>
inline bool chmax(T &a, T b) { return ((a < b) ? (a = b, true) : (false)); }
template <typename T>
inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false)); }
template <class T1, class T2>
inline auto mod(T1 x, T2 r) { return (x % r + r) % r; }

// ======================================== //

int main()
{
    int N, K;
    string S;
    cin >> N >> K >> S;

    rep(i, 0, N)
    {
        if (S[i] == '?' && ((i > 0 && S[i - 1] == 'o') || (i < N - 1 && S[i + 1] == 'o')))
        {
            S[i] = '.';
        }
    }

    vector<int> T(N);
    int num_o = 0, max_o = 0;
    int q_length = 0;
    rep(i, 0, N)
    {
        if (S[i] == '.')
        {
            T[i] = -1;
        }
        else if (S[i] == 'o')
        {
            T[i] = 0;
            num_o++;
            max_o++;
        }
        else if (S[i] == '?')
        {
            q_length++;
            if (S[i + 1] != '?')
            {
                rep(j, 0, q_length) T[i - j] = q_length;
                max_o += div_ceil(q_length, 2);
                q_length = 0;
            }
        }
    }

    if (num_o == K)
    {
        rep(i, 0, N)
        {
            if (T[i] > 0)
                T[i] = -1;
        }
    }

    if (max_o == K)
    {
        rep(i, 0, N)
        {
            if (T[i] > 0 && T[i] % 2 == 1)
            {
                int l = T[i];
                rep(j, 0, l)
                {
                    if (j % 2 == 1)
                        T[i + j] = -1;
                    else
                        T[i + j] = 0;
                }
            }
        }
    }

    for (auto &&x : T)
    {
        if (x == -1)
            cout << '.';
        else if (x == 0)
            cout << 'o';
        else
            cout << '?';
    }
    cout << endl;

    return 0;
}