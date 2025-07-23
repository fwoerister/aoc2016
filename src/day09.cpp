#include <iostream>
#include <regex>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

class Decompressor
{
private:
    map<string, string> cache;

public:
    string decompressP1(string compressedStr);
    string decompressP2(string compressedStr);
};

string Decompressor::decompressP1(string compressedStr)
{
    string originalStr(compressedStr);
    stringstream outputStr;

    int idx = 0;

    regex regExp("\\((\\d+)x(\\d+)\\)");
    smatch match;

    regex_search(compressedStr, match, regExp);

    while (match.position() < compressedStr.length())
    {
        while (idx < match.position())
            outputStr << compressedStr[idx++];

        int markerLen = match.str().length();

        for (int i = 0; i < stoi(match[2]); ++i)
            outputStr << compressedStr.substr(idx + markerLen, stoi(match[1]));

        compressedStr.erase(0, idx + markerLen + stoi(match[1]));
        idx = 0;
        regex_search(compressedStr, match, regExp);
    }

    outputStr << compressedStr;

    return outputStr.str();
}

string Decompressor::decompressP2(string compressedStr)
{
    string originalStr(compressedStr);

    if (cache.count(compressedStr) != 0)
    {
        return cache[compressedStr];
    }

    stringstream outputStr;

    int idx = 0;

    regex regExp("\\((\\d+)x(\\d+)\\)");
    smatch match;

    regex_search(compressedStr, match, regExp);

    while (match.position() < compressedStr.length())
    {
        while (idx < match.position())
            outputStr << compressedStr[idx++];

        int markerLen = match.str().length();

        for (int i = 0; i < stoi(match[2]); ++i)
            outputStr << decompressP2(compressedStr.substr(idx + markerLen, stoi(match[1])));

        compressedStr.erase(0, idx + markerLen + stoi(match[1]));
        idx = 0;
        regex_search(compressedStr, match, regExp);
    }

    outputStr << compressedStr;
    cache[originalStr] = outputStr.str();

    return outputStr.str();
}

int main()
{
    ifstream f("input/day09.txt");
    string line;

    getline(f, line);

    Decompressor d;

    cout << "Part 1:" << endl;
    cout << d.decompressP1(line).length() << endl;
    cout << "Part 2:" << endl;
    cout << d.decompressP2(line).length() << endl;
}