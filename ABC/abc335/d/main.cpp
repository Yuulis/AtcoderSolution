#include <bits/stdc++.h>
// #include <atcoder/all>

#define all(x) (x).begin(), (x).end()
#define fix(x) fixed << setprecision(x)
#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)
#define rrep(i, start, end) for (auto i = (start); (i) >= (end); (i)--)

constexpr auto PI = 3.14159265358979;
constexpr auto INF = 1e+9;
constexpr auto INFL = 1LL << 60;

using namespace std;
// using namespace atcoder;
using ll = long long;
using lld = long double;
// using mint = modint1000000007;
// using mint = modint998244353;
using Pair_int = pair<int, int>;
using Pair_ll = pair<ll, ll>;

ll ceil(ll a, ll b)
{
    if (a < 0 && b > 0)
        return a / b;
    if (a % b == 0)
        return a / b;
    return (a / b) + 1;
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
template <class T>
bool chmax(T &a, const T &b)
{
    if (a < b)
    {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
bool chmin(T &a, const T &b)
{
    if (b < a)
    {
        a = b;
        return 1;
    }
    return 0;
}
template <class T1, class T2>
inline auto mod(T1 x, T2 r) { return (x % r + r) % r; }

// ======================================== //

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int main()
{
    int N;
    cin >> N;

    vector<vector<int>> grid(N, vector<int>(N));
    int x = 0, y = 0;
    int cnt = 1;
    int dir = 0;
    while (cnt < N * N)
    {
        grid[y][x] = cnt;

        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (0 <= nx && nx < N && 0 <= ny && ny < N && grid[ny][nx] == 0)
        {
            x = nx;
            y = ny;
            cnt++;
        }
        else
        {
            dir = (dir + 1) % 4;
        }
    }

    rep(i, 0, N)
    {
        rep(j, 0, N)
        {
            if (i == (N - 1) / 2 && j == (N - 1) / 2)
                cout << 'T' << " ";
            else
                cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}