#include <iostream>
#include <fstream>

using namespace std;

struct HyperRange
{
    HyperRange(int start, int end) : start(start), end(end) {}

    int start;
    int end;
};

class IPv7Analyzer
{
private:
    string ip;
    vector<int> supernetABBAs;
    vector<int> hypernetABBAs;
    vector<int> supernetABAs;
    vector<int> hypernetABAs;

    bool isAbbaAt(int idx)
    {
        if (idx + 3 > ip.length())
            return false;

        if (ip[idx] == ip[idx + 3] && ip[idx + 1] == ip[idx + 2] && ip[idx] != ip[idx + 1])
            return true;

        return false;
    }

    bool isAbaAt(int idx)
    {
        if (idx + 2 > ip.length())
            return false;

        if (ip[idx] == ip[idx + 2] && ip[idx] != ip[idx + 1])
            return true;

        return false;
    }

    bool containsHyperBAB(char a, char b)
    {
        for (int idx : hypernetABAs)
        {
            if (ip[idx] == b && ip[idx + 1] == a && ip[idx + 2] == b)
                return true;
        }
        return false;
    }

public:
    IPv7Analyzer(string ip) : ip(ip)
    {
        bool isHyper = false;
        int idx = 0;

        while (idx < ip.length())
        {
            if (ip[idx] == '[')
                isHyper = true;
            else if (ip[idx] == ']')
                isHyper = false;
            else
            {
                if (isAbaAt(idx) && isHyper)
                    hypernetABAs.push_back(idx);
                else if (isAbaAt(idx))
                    supernetABAs.push_back(idx);

                if (isAbbaAt(idx) && isHyper)
                    hypernetABBAs.push_back(idx);
                else if (isAbbaAt(idx))
                    supernetABBAs.push_back(idx);
            }
            ++idx;
        }
    }

    bool supportsTLS();
    bool supportsSSL();
};

bool IPv7Analyzer::supportsTLS()
{
    return supernetABBAs.size() != 0 && hypernetABBAs.size() == 0;
}

bool IPv7Analyzer::supportsSSL()
{
    for (int idx : supernetABAs)
    {
        char a = ip[idx], b = ip[idx + 1];

        if (containsHyperBAB(a, b))
            return true;
    }
    return false;
}

int main()
{
    ifstream f("input/day07.txt");
    string line;

    int tlsCount = 0, sslCount = 0;

    while (getline(f, line))
    {
        IPv7Analyzer analyzer(line);

        if (analyzer.supportsTLS())
            ++tlsCount;
        if (analyzer.supportsSSL())
            ++sslCount;
    }

    cout << "Addresses supporting TLS: " << tlsCount << "\n";
    cout << "Addresses supporting SSL: " << sslCount << "\n";
}