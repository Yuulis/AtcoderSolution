#include <string>
#include <vector>

std::vector<std::pair<char, int>> encode(const std::string& str) {
    int n = (int)str.size();
    std::vector<std::pair<char, int>> res;
    for (int l = 0; l < n;) {
        int r = l + 1;
        for (; r < n && str[l] == str[r]; r++) {};
        res.push_back({str[l], r - l});
        l = r;
    }
    return res;
}

std::string decode(const std::vector<std::pair<char, int>>& code) {
    std::string res = "";
    for (auto p : code) {
        for (int i = 0; i < p.second; i++) {
            res.push_back(p.first);
        }
    }
    return res;
}