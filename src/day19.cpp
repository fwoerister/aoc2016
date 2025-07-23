#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int findSolutionP1(int n)
{
    vector<int> elfs;

    for (int i = 0; i < n; i++)
    {
        elfs.push_back(i + 1);
    }

    int idx = 0;
    int remainingElfs = n;

    while (remainingElfs > 1)
    {
        int kickedElf = (idx + 1) % remainingElfs;
        elfs.erase(elfs.begin() + kickedElf);

        --remainingElfs;
        if (kickedElf < idx)
            --idx;

        idx = (idx + 1) % remainingElfs;
    }

    return elfs[0];
}

int findSolutionP2(int n)
{
    vector<int> elfs;

    for (int i = 0; i < n; i++)
    {
        elfs.push_back(i + 1);
    }

    int idx = 0;
    int remainingElfs = n;

    while (remainingElfs > 1)
    {
        int kickedElf = (idx + (remainingElfs / 2)) % remainingElfs;
        elfs.erase(elfs.begin() + kickedElf);

        --remainingElfs;
        if (kickedElf < idx)
            --idx;

        idx = (idx + 1) % remainingElfs;
    }

    return elfs[0];
}

int main()
{
    ifstream f("input/day19.txt");
    string line;

    getline(f, line);
    int n = stoi(line);

    cout << findSolutionP1(n) << endl;
    cout << findSolutionP2(n) << endl;
}