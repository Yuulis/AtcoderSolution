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

vector<int> buildDP(const vector<Pair_int> &v, int X)
{
    int n = v.size();
    vector<vector<int>> dp(n + 1, vector<int>(X + 1, 0));
    rep(i, 0, n)
    {
        int vitamin = v[i].first, calorie = v[i].second;
        repe(c, 0, X)
        {
            if (c >= calorie)
            {
                dp[i + 1][c] = max(dp[i][c], dp[i][c - calorie] + vitamin);
            }
            else
            {
                dp[i + 1][c] = dp[i][c];
            }
        }
    }

    return dp[n];
}

int getMinCalorie(const vector<int> &dp, int vitamin)
{
    rep(c, 0, dp.size())
    {
        if (dp[c] >= vitamin)
        {
            return c;
        }
    }

    return INF;
}

int main()
{
    int N, X;
    cin >> N >> X;
    vector<Pair_int> v1, v2, v3;
    ll v1_sum = 0, v2_sum = 0, v3_sum = 0;
    rep(i, 0, N)
    {
        int V, A, C;
        cin >> V >> A >> C;

        if (V == 1)
        {
            v1.push_back({A, C});
            v1_sum += A;
        }
        else if (V == 2)
        {
            v2.push_back({A, C});
            v2_sum += A;
        }
        else
        {
            v3.push_back({A, C});
            v3_sum += A;
        }
    }

    vector<int> dp1 = buildDP(v1, X);
    vector<int> dp2 = buildDP(v2, X);
    vector<int> dp3 = buildDP(v3, X);

    ll ok = 0, ng = min({v1_sum, v2_sum, v3_sum}) + 1;
    while (ng - ok > 1)
    {
        ll mid = (ok + ng) / 2;
        int c1 = getMinCalorie(dp1, mid);
        int c2 = getMinCalorie(dp2, mid);
        int c3 = getMinCalorie(dp3, mid);

        if ((ll)c1 + c2 + c3 <= X)
        {
            ok = mid;
        }
        else
        {
            ng = mid;
        }
    }

    cout << ok << endl;

    return 0;
}