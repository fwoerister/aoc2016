#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

struct Disc
{
    int delay;
    int periode;

    Disc(int delay, int periode) : delay(delay), periode(periode) {}
};

bool areEqual(vector<Disc> discs)
{
    for (Disc d : discs)
        if (discs[0].delay != d.delay)
            return false;

    return true;
}

int findDelay(vector<Disc> discs)
{
    while (!areEqual(discs))
    {
        int smallestIdx = 0;

        for (int idx = 1; idx < discs.size(); idx++)
        {
            if (discs[smallestIdx].delay > discs[idx].delay)
                smallestIdx = idx;
        }

        discs[smallestIdx].delay += discs[smallestIdx].periode;
    }

    return discs[0].delay;
}

int main()
{
    ifstream f("input/day15.txt");
    string line;

    vector<Disc> discs;

    while (getline(f, line))
    {
        regex r("Disc #(\\d+) has (\\d+) positions; at time=(\\d+), it is at position (\\d+).");
        smatch m;

        regex_search(line, m, r);

        int delay = stoi(m[2]) - ((stoi(m[1]) + stoi(m[4])) % stoi(m[2]));

        discs.push_back(Disc(delay, stoi(m[2])));
    }

    cout << findDelay(discs) << endl;

    discs.push_back(Disc(4, 11));

    cout << findDelay(discs) << endl;
}