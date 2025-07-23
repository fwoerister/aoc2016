#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

bool isSafe(string line, int pos)
{
    if (pos < 0 || pos >= line.length())
        return true;

    return line[pos] == '.';
}

string getNextLine(string line)
{
    stringstream ss;

    for (int idx = 0; idx < line.length(); idx++)
    {
        if (isSafe(line, idx - 1) && isSafe(line, idx) && !isSafe(line, idx + 1))
            ss << '^';
        else if (!isSafe(line, idx - 1) && isSafe(line, idx) && isSafe(line, idx + 1))
            ss << '^';
        else if (isSafe(line, idx - 1) && !isSafe(line, idx) && !isSafe(line, idx + 1))
            ss << '^';
        else if (!isSafe(line, idx - 1) && !isSafe(line, idx) && isSafe(line, idx + 1))
            ss << '^';
        else
            ss << '.';
    }

    return ss.str();
}

int countSafeTiles(string line)
{
    int safeCount = 0;

    for (char c : line)
        if (c == '.')
            safeCount++;

    return safeCount;
}

int main()
{
    ifstream f("input/day18.txt");
    string line;

    getline(f, line);

    int safeCount = countSafeTiles(line);

    for (int i = 0; i < 40 - 1; i++)
    {
        line = getNextLine(line);

        safeCount += countSafeTiles(line);
    }

    cout << safeCount << endl;

    for (int i = 0; i < (400000 - 40); i++)
    {
        line = getNextLine(line);

        safeCount += countSafeTiles(line);
    }

    cout << safeCount << endl;
}