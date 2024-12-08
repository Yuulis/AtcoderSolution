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

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main()
{
    int H, W, D;
    cin >> H >> W >> D;
    vector<string> S(H);
    rep(i, 0, H) cin >> S[i];

    vector<vector<bool>> isHumid(H, vector<bool>(W, false));
    queue<tuple<int, int, int>> queue;
    rep(i, 0, H)
    {
        rep(j, 0, W)
        {
            if (S[i][j] == 'H')
            {
                queue.emplace(i, j, 0);
                isHumid[i][j] = true;
            }
        }
    }

    while (!queue.empty())
    {
        auto [x, y, dist] = queue.front();
        queue.pop();

        if (dist >= D)
            continue;

        rep(i, 0, 4)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= H || ny < 0 || ny >= W || S[nx][ny] == '#' || isHumid[nx][ny])
                continue;

            isHumid[nx][ny] = true;
            queue.emplace(nx, ny, dist + 1);
        }
    }

    int ans = 0;
    rep(i, 0, H) rep(j, 0, W) if (isHumid[i][j]) ans++;

    cout << ans << endl;
}