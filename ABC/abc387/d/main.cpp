#include <bits/stdc++.h>
#include <atcoder/all>

#define all(x) (x).begin(), (x).end()
#define fix(x) fixed << setprecision(x)
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define rrep(i, start, end) for (auto i = (start); (i) >= (end); (i)--)

constexpr auto PI = 3.14159265358979;
constexpr int INF = 1e+9;
constexpr long long INFL = 1LL << 60;

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

int di[2][2] = {{-1, 1}, {0, 0}};
int dj[2][2] = {{0, 0}, {-1, 1}};

struct State
{
    int i, j, dir;
};

int main()
{
    int H, W;
    cin >> H >> W;
    vector<vector<char>> grid(H, vector<char>(W));
    Pair_int start, goal;
    rep(i, 0, H)
    {
        rep(j, 0, W)
        {
            cin >> grid[i][j];

            if (grid[i][j] == 'S')
                start = {i, j};

            if (grid[i][j] == 'G')
                goal = {i, j};
        }
    }
    vector<vector<vector<int>>> dist(H, vector<vector<int>>(W, vector<int>(2, INF)));
    dist[start.first][start.second][0] = 0;
    dist[start.first][start.second][1] = 0;

    queue<State> que;
    que.push({start.first, start.second, 0});
    que.push({start.first, start.second, 1});

    while (!que.empty())
    {
        State now = que.front();
        que.pop();

        rep(k, 0, 2)
        {
            int ni = now.i + di[now.dir][k];
            int nj = now.j + dj[now.dir][k];
            int nd = (now.dir + 1) % 2;

            if (ni < 0 || ni >= H || nj < 0 || nj >= W)
                continue;

            if (grid[ni][nj] == '#')
                continue;

            if (dist[ni][nj][nd] != INF)
                continue;

            dist[ni][nj][nd] = dist[now.i][now.j][now.dir] + 1;
            que.push({ni, nj, nd});
        }
    }

    int ans = min(dist[goal.first][goal.second][0], dist[goal.first][goal.second][1]);
    if (ans == INF)
        cout << -1 << endl;
    else
        cout << ans << endl;

    return 0;
}