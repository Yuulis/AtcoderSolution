#include <string>
#include <vector>

std::vector<std::pair<char, int>> run_length_encoding(const std::string &str)
{
    int n = (int)str.size();
    std::vector<std::pair<char, int>> res;
    int cnt = 1;
    for (int i = 1; i < n; i++)
    {
        if (str[i] != str[i - 1])
        {
            res.push_back({str[i - 1], cnt});
            cnt = 0;
        }
        cnt++;
    }
    res.push_back({str.back(), cnt});

    return res;
}

std::string decode_run_length(const std::vector<std::pair<char, int>> &code)
{
    std::string res = "";
    for (auto p : code)
    {
        for (int i = 0; i < p.second; i++)
            res.push_back(p.first);
    }

    return res;
}
