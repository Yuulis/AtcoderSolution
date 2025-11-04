#include <bits/stdc++.h>
#include <atcoder/all>

#define all(x) (x).begin(), (x).end()
#define fix(x) fixed << setprecision(x)
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define rrep(i, start, end) for (auto i = (start); (i) >= (end); (i)--)

constexpr auto PI = 3.14159265358979;
constexpr auto INF = 1e+9;
constexpr auto INFL = 1LL << 60;

using namespace std;
using namespace atcoder;
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
ll pow(ll x, ll n)
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
    int N, M;
    ll Sx, Sy;
    cin >> N >> M >> Sx >> Sy;
    map<ll, set<ll>> houses_on_x, houses_on_y;
    rep(i, 0, N)
    {
        ll X, Y;
        cin >> X >> Y;
        houses_on_x[X].insert(Y);
        houses_on_y[Y].insert(X);
    }

    ll pos_x = Sx, pos_y = Sy, ans = 0;
    rep(i, 0, M)
    {
        char D;
        ll C;
        cin >> D >> C;

        ll dx = 0, dy = 0;
        if (D == 'U')
            dy = C;
        else if (D == 'D')
            dy = -C;
        else if (D == 'L')
            dx = -C;
        else if (D == 'R')
            dx = C;

        if (dx == 0)
        {
            ll min_y = min(pos_y, pos_y + dy);
            ll max_y = max(pos_y, pos_y + dy);

            auto itr = houses_on_x[pos_x].lower_bound(min_y);
            while (itr != houses_on_x[pos_x].end() && *itr <= max_y)
            {
                ans++;
                houses_on_y[*itr].erase(pos_x);
                itr = houses_on_x[pos_x].erase(itr);
            }
        }
        else if (dy == 0)
        {
            ll min_x = min(pos_x, pos_x + dx);
            ll max_x = max(pos_x, pos_x + dx);

            auto itr = houses_on_y[pos_y].lower_bound(min_x);
            while (itr != houses_on_y[pos_y].end() && *itr <= max_x)
            {
                ans++;
                houses_on_x[*itr].erase(pos_y);
                itr = houses_on_y[pos_y].erase(itr);
            }
        }

        pos_x += dx;
        pos_y += dy;
    }

    cout << pos_x << " " << pos_y << " " << ans << endl;
}