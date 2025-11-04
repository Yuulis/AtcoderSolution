#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

vector<int> create_next_table(const string &pattern)
{
    int n = pattern.size();
    vector<int> next(n, 0);

    int j = 0;
    rep(i, 1, n)
    {
        while (j > 0 && pattern[i] != pattern[j])
        {
            j = next[j - 1];
        }

        if (pattern[i] == pattern[j])
        {
            j++;
        }

        next[i] = j;
    }
    return next;
}

int kmp_search(const string &text, const string &pattern)
{
    int m = text.size();
    int n = pattern.size();

    if (n == 0)
        return 0;

    if (m < n)
        return -1;

    vector<int> next = create_next_table(pattern);

    int j = 0;
    rep(i, 0, m)
    {
        while (j > 0 && text[i] != pattern[j])
        {
            j = next[j - 1];
        }

        if (text[i] == pattern[j])
        {
            j++;
        }

        if (j == n)
        {
            return i - n + 1;
        }
    }

    return -1;
}

int solve()
{
    string A, B;
    cin >> A >> B;

    string text = A + A;
    int ans = kmp_search(text, B);

    return ans;
}

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        cout << solve() << endl;
    }

    return 0;
}