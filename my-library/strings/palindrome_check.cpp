#include <string>

bool isPalindrome(std::string s)
{
    int l = s.size();
    for (int i = 0; i < l / 2; i++)
    {
        if (s[i] != s[l - i - 1])
            return false;
    }
    return true;
}