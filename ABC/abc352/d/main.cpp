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
// using mint = modint998244353;
using Pair_int = pair<int, int>;
using Pair_ll = pair<ll, ll>;
template <class T>
using Graph = vector<vector<T>>;

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
template <typename T>
inline bool chmax(T &a, T b) { return ((a < b) ? (a = b, true) : (false)); }
template <typename T>
inline bool chmin(T &a, T b) { return ((a > b) ? (a = b, true) : (false)); }
template <class T1, class T2>
inline auto mod(T1 x, T2 r) { return (x % r + r) % r; }

// ======================================== //

// int main()
// {
//     int N, K;
//     cin >> N >> K;
//     vector<int> v(N);
//     rep(i, 0, N)
//     {
//         int P;
//         cin >> P;
//         P--;
//         v[P] = i;
//     }

//     set<int> st;
//     rep(i, 0, K) st.insert(v[i]);

//     int ans = *st.rbegin() - *st.begin();
//     rep(i, 0, N - K)
//     {
//         st.erase(v[i]);
//         st.insert(v[i + K]);
//         chmin(ans, *st.rbegin() - *st.begin());
//     }

//     cout << ans << endl;
// }

// ======================================== //
// セグ木解法

int op_min(int a, int b) { return min(a, b); }
int e_min() { return INF; }

int op_max(int a, int b) { return max(a, b); }
int e_max() { return 0; }

int main()
{
    int N, K;
    cin >> N >> K;
    segtree<int, op_min, e_min> segMin(N);
    segtree<int, op_max, e_max> segMax(N);
    rep(i, 0, N)
    {
        int P;
        cin >> P;
        segMin.set(P - 1, i);
        segMax.set(P - 1, i);
    }

    int ans = INF;
    rep(i, 0, N - K + 1)
    {
        int min = segMin.prod(i, i + K);
        int max = segMax.prod(i, i + K);
        chmin(ans, max - min);
    }
    cout << ans << endl;
}