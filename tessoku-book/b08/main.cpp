#include <bits/stdc++.h>
// #include <atcoder/all>

#define all(x) (x).begin(), (x).end()
#define fix(x) fixed << setprecision(x)
#define rep(i, start, end) for (ll i = (start); i < (ll)(end); i++)
#define rrep(i, start, end) for (ll i = ((ll)(start)); i >= (end); i--)

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
using Grid = vector<string>;

struct Edge
{
    int to;
    int cost;
};

ll ceil(ll a, ll b)
{
    if (a % b == 0)
        return a / b;
    return (a / b) + 1;
}
/*
mint modPow(ll x, ll n)
{
    mint ans = 1;
    for (ll i = 0; i < n; i++)
        ans *= x;
    return ans;
}
*/
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
template <class T>
using Graph = vector<vector<T>>;

// ======================================== //

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> v(1515, vector<int>(1515, 0));
    rep(i, 0, N)
    {
        int X, Y;
        cin >> X >> Y;

        v[X][Y]++;
    }

    vector<vector<int>> ps(1515, vector<int>(1515, 0));
    rep(i, 0, 1500) rep(j, 0, 1500) ps[i + 1][j + 1] = ps[i + 1][j] + ps[i][j + 1] - ps[i][j] + v[i + 1][j + 1];

    int Q;
    cin >> Q;
    rep(i, 0, Q)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        cout << ps[a - 1][b - 1] - ps[a - 1][d] - ps[c][b - 1] + ps[c][d] << endl;
    }
}