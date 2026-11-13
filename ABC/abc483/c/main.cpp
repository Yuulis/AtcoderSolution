#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

using Pair_int = pair<int, int>;

// ======================================== //

struct Comp {
    bool operator()(const Pair_int& a, const Pair_int& b) const {
        if (a.first != b.first) {
            return a.first > b.first;
        }
        return a.second < b.second;
    }
};

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> cnt(N, 0);
    vector<vector<int>> second(N);
    rep(i, 0, M) {
        int A, B;
        cin >> A >> B;
        A--, B--;

        cnt[A]++;
        second[A].push_back(B);
    }

    set<Pair_int, Comp> st;
    rep(i, 0, N) {
        st.insert({ cnt[i], i });
    }

    rep(k, 0, N) {
        st.erase({ cnt[k], k });

        for (auto x : second[k]) {
            st.erase({ cnt[x], x });
            cnt[x]++;
            st.insert({ cnt[x], x });
        }

        cout << st.begin()->second + 1 << endl;

        for (auto x : second[k]) {
            st.erase({ cnt[x], x });
            cnt[x]--;
            st.insert({ cnt[x], x });
        }

        st.insert({ cnt[k], k });
    }

    return 0;
}