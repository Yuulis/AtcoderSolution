#include <vector>
#include <utility>

template <typename T>
std::vector<std::pair<T, T>> prime_factor(T n) {
    std::vector<std::pair<T, T>> res;
    for (T i = 2; i * i <= n; i++) {
        if (n % i != 0) continue;

        T tmp = 0;
        while (n % i == 0) {
            tmp++;
            n /= i;
        }

        res.push_back(make_pair(i, tmp));
    }

    if (n != 1) res.push_back(make_pair(n, 1));
    
    return res;
}