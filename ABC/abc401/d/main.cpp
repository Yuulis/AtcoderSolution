#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

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

// ======================================== //

int main()
{
    int N, K;
    string S;
    cin >> N >> K >> S;

    rep(i, 0, N)
    {
        if (S[i] == '?' && ((i > 0 && S[i - 1] == 'o') || (i < N - 1 && S[i + 1] == 'o')))
        {
            S[i] = '.';
        }
    }

    vector<int> T(N);
    int num_o = 0, max_o = 0;
    int q_length = 0;
    rep(i, 0, N)
    {
        if (S[i] == '.')
        {
            T[i] = -1;
        }
        else if (S[i] == 'o')
        {
            T[i] = 0;
            num_o++;
            max_o++;
        }
        else if (S[i] == '?')
        {
            q_length++;
            if (S[i + 1] != '?')
            {
                rep(j, 0, q_length) T[i - j] = q_length;
                max_o += div_ceil(q_length, 2);
                q_length = 0;
            }
        }
    }

    if (num_o == K)
    {
        rep(i, 0, N)
        {
            if (T[i] > 0)
                T[i] = -1;
        }
    }

    if (max_o == K)
    {
        rep(i, 0, N)
        {
            if (T[i] > 0 && T[i] % 2 == 1)
            {
                int l = T[i];
                rep(j, 0, l)
                {
                    if (j % 2 == 1)
                        T[i + j] = -1;
                    else
                        T[i + j] = 0;
                }
            }
        }
    }

    for (auto &&x : T)
    {
        if (x == -1)
            cout << '.';
        else if (x == 0)
            cout << 'o';
        else
            cout << '?';
    }
    cout << endl;

    return 0;
}