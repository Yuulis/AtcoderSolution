#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s = ",a,b,,c,";
    // Add a dummy delimiter character at the end of the string to be split so that trailing whitespace is not ignored if the end of the string to be split is a delimiter character.
    stringstream ss{s + ','};
    vector<string> v;
    string buf;
    while (getline(ss, buf, ','))
        if (!buf.empty())
            v.push_back(buf);

    for (auto &&s : v)
    {
        cout << s << endl;
    }

    /* output :
    a
    b
    c
    */
}

// ref : https://marycore.jp/prog/cpp/std-string-split/