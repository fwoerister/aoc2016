#include <iostream>
#include <list>
#include <fstream>
#include <regex>

using namespace std;

struct Range
{
    long start, end;

    Range(long start, long end) : start(start), end(end) {}

    bool operator==(const Range &other) const
    {
        return start == other.start && end == other.end;
    }

    bool operator!=(const Range &other) const
    {
        return !(*this == other);
    }
};

bool compareByStart(Range a, Range b)
{
    return a.start < b.start;
}

bool compareByEnd(Range a, Range b)
{
    return a.end < b.end;
}

list<Range> loadRanges(string filename)
{
    ifstream f(filename);
    string line;

    list<Range> ranges;

    while (getline(f, line))
    {
        regex r("(\\d+)-(\\d+)");
        smatch m;

        regex_search(line, m, r);

        Range newRange(stod(m[1]), stod(m[2]));
        ranges.push_back(newRange);
    }

    return ranges;
}

long findBlockedIPCount(list<Range> ranges)
{
    ranges.sort(compareByStart);

    long highestIP = -1;
    long ipCount = 0;

    for (Range r : ranges)
    {
        long correctedStart = r.start;

        if (r.start < highestIP)
        {
            correctedStart = highestIP + 1;
        }

        if (r.end > highestIP)
        {
            ipCount += (r.end - correctedStart) + 1;
            highestIP = r.end;
        }
    }

    return ipCount;
}

long findLowest(list<Range> ranges)
{
    list<Range> rangesByStart = ranges;
    rangesByStart.sort(compareByStart);

    list<Range> rangesByEnd(ranges);
    rangesByEnd.sort(compareByEnd);

    if (rangesByStart.front().start != 0)
        cout << 0 << endl;

    else
        for (Range r1 : rangesByEnd)
        {
            bool isLowest = true;
            for (Range r2 : rangesByStart)
            {
                if (r1 == r2)
                    continue;
                if (r2.start <= r1.end + 1 && r2.end >= r1.end + 1)
                    isLowest = false;
            }

            if (isLowest)
            {
                return r1.end + 1;
            }
        }
    return -1;
}

int main()
{
    long max = 4294967296;

    list<Range> ranges = loadRanges("input/day20.txt");

    cout << findLowest(ranges) << endl;
    cout << max - findBlockedIPCount(ranges) << endl;
}