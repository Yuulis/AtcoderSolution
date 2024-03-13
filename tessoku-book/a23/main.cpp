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
    int N, M;
    cin >> N >> M;
    vector<vector<int>> A(110, vector<int>(20));
    rep(i, 1, M + 1) rep(j, 1, N + 1) cin >> A[i][j];

    vector<vector<int>> dp(110, vector<int>(1024, INF));
    dp[0][0] = 0;
    rep(i, 1, M + 1)
    {
        rep(j, 0, (1 << N))
        {
            vector<bool> flag(20, false);
            rep(k, 1, N + 1)
            {
                if ((j / (1 << (k - 1))) % 2 == 1)
                    flag[k] = true;
            }

            int num = 0;
            rep(k, 1, N + 1)
            {
                if (flag[k] || A[i][k] == 1)
                    num += (1 << (k - 1));
            }

            dp[i][j] = min(dp[i][j], dp[i - 1][j]);
            dp[i][num] = min(dp[i][num], dp[i - 1][j] + 1);
        }
    }

    if (dp[M][(1 << N) - 1] == INF)
        cout << -1 << endl;
    else
        cout << dp[M][(1 << N) - 1] << endl;
}