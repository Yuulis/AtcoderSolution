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

int N, M;
vector<int> ans;

void dfs(Graph<int> &G, vector<bool> &flag, int pos, vector<int> &path)
{
    if (pos == N)
    {
        ans = path;
        return;
    }

    flag[pos] = true;
    for (auto next : G[pos])
    {
        if (!flag[next])
        {
            path.push_back(next);
            dfs(G, flag, next, path);
            path.pop_back();
        }
    }
    return;
}

int main()
{
    cin >> N >> M;
    Graph<int> G(N + 1);
    rep(i, 0, M)
    {
        int A, B;
        cin >> A >> B;
        G[A].push_back(B);
        G[B].push_back(A);
    }

    vector<bool> flag(N + 1, false);
    vector<int> path;
    path.push_back(1);
    dfs(G, flag, 1, path);

    for (auto &&i : ans)
    {
        cout << i << " ";
    }
    cout << endl;
}