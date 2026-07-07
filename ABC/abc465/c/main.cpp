#include <bits/stdc++.h>
using namespace std;

#define rep(i, start, end) for (auto i = (start); (i) < (end); (i)++)

// ======================================== //

int main()
{
    int N;
    string S;
    cin >> N >> S;

    deque<int> que;
    bool reversed = false;
    rep(k, 0, N) {
        if (S[k] == 'o') {
            reversed = !reversed;
            if (reversed) {
                que.push_back(k);
            }
            else {
                que.push_front(k);
            }
        }
        else {
            if (reversed) {
                que.push_front(k);
            }
            else {
                que.push_back(k);
            }
        }
    }

    if (reversed) {
        while (!que.empty()) {
            cout << que.back() + 1 << " ";
            que.pop_back();
        }
    }
    else {
        while (!que.empty()) {
            cout << que.front() + 1 << " ";
            que.pop_front();
        }
    }
    cout << endl;

    return 0;
}