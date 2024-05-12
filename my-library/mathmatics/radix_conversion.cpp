#include <iostream>
#include <bitset>
#include <string>
#include <cassert>
#include <sstream>

int main()
{
    // decimal -> binary (filled with eight 0s)
    unsigned x = 0;
    std::cout << static_cast<std::bitset<8>>(x) << std::endl;

    // Example
    std::cout << static_cast<std::bitset<8>>(10) << std::endl; // 00001010
}

// Arbitrary radix conversion
std::string radix_conversion(const std::string x, const int from, const int to)
{
    // Conversion table.
    // To be changed as appropriate.
    const std::string table = "0123456789abcdef";
    assert((2 <= from && from <= 16) && (2 <= to && to <= 16));

    unsigned long sum = 0;
    for (char c : x)
    {
        sum = sum * from + table.find(c);
    }

    std::string res = "";
    do
    {
        int mod = sum % to;
        res = table[mod] + res;
        sum /= to;
    } while (sum);

    return res;
}

// Example
int main()
{
    std::string x = "110";
    std::cout << radix_conversion(x, 2, 10) << std::endl; // 6
}