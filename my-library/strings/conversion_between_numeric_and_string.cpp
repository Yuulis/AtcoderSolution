#include <iostream>
#include <string>

int main()
{
    // int -> string
    int n = 12345;
    std::string s = std::to_string(n);

    // int -> char
    int x = 7;
    char ch = char(x + '0');

    // string -> int / double
    std::string a = "123";
    std::string b = "0012";
    std::string c = "123.456";

    int p = std::stoi(a);
    int q = std::stoi(b); // 12
    double r = std::stod(c);

    // char -> int
    char cha = '7';
    int x = int(cha - '0');
    std::cout << x << std::endl;

    // one by one
    std::string s = "12345";
    for (int i = 0; i < s.size(); i++)
    {
        std::cout << int(s[i] - '0') << " ";
    }
}