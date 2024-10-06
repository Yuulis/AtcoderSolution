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

struct Line
{
    int x1, y1, x2, y2;
};

double dist(int &x1, int &y1, int &x2, int &y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main()
{
    int N, S, T;
    cin >> N >> S >> T;
    vector<Line> lines(N);
    rep(i, 0, N) cin >> lines[i].x1 >> lines[i].y1 >> lines[i].x2 >> lines[i].y2;

    vector<int> order(N);
    iota(all(order), 0);

    double ans = INF;
    do {
        rep(bit, 0, (1 << N)) {
            double sum = 0;
            int pos_x = 0, pos_y = 0;
            rep(i, 0, N) {
                if (bit & (1 << i)) {
                    sum += dist(pos_x, pos_y, lines[order[i]].x1, lines[order[i]].y1) / S;
                    pos_x = lines[order[i]].x2;
                    pos_y = lines[order[i]].y2;
                } else {
                    sum += dist(pos_x, pos_y, lines[order[i]].x2, lines[order[i]].y2) / S;
                    pos_x = lines[order[i]].x1;
                    pos_y = lines[order[i]].y1;
                }

                sum += dist(lines[order[i]].x1, lines[order[i]].y1, lines[order[i]].x2, lines[order[i]].y2) / T;
            }

            chmin(ans, sum);
        }
    } while (next_permutation(all(order)));

    cout << fix(12) << ans << endl;
}