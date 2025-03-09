#include <iostream>
#include <sstream>
#include <vector>
//WA on #8
using namespace std;
typedef long long ll;
string h2b(const string &h)
{
    stringstream ss;
    for (char c : h)
    {
        switch (c)
        {
            // 比较小型的打表。
        case '0':
            ss << "0000";
            break;
        case '1':
            ss << "0001";
            break;
        case '2':
            ss << "0010";
            break;
        case '3':
            ss << "0011";
            break;
        case '4':
            ss << "0100";
            break;
        case '5':
            ss << "0101";
            break;
        case '6':
            ss << "0110";
            break;
        case '7':
            ss << "0111";
            break;
        case '8':
            ss << "1000";
            break;
        case '9':
            ss << "1001";
            break;
        case 'A':
            ss << "1010";
            break;
        case 'a':
            ss << "1010";
            break;
        case 'B':
            ss << "1011";
            break;
        case 'b':
            ss << "1011";
            break;
        case 'C':
            ss << "1100";
            break;
        case 'c':
            ss << "1100";
            break;
        case 'D':
            ss << "1101";
            break;
        case 'd':
            ss << "1101";
            break;
        case 'E':
            ss << "1110";
            break;
        case 'e':
            ss << "1110";
            break;
        case 'F':
            ss << "1111";
            break;
        case 'f':
            ss << "1111";
            break;
        }
    }
    return ss.str();
}

int main()
{
    string ip;
    cin >> ip;

    vector<string> p;
    stringstream ss(ip);
    string part;

    while (getline(ss, part, ':'))
        p.push_back(part);

    if (ip.find("::") != string::npos)
    {
        vector<string> exp;
        int miss = 8 - p.size() + 1;
        for (const string &x : p)
        {
            if (x.empty())
            {
                for (int i = 0; i < miss; ++i)
                    exp.push_back("0000");
            }
            else
            {
                exp.push_back(x);
            }
        }
        p = exp;
    }

    string bip;
    for (const string &x : p)
    {
        string bin = h2b(x);
        while (bin.size() < 16)
            bin = "0" + bin;
        bip += bin;
    }

    cout << bip << endl;

    return 0;
}