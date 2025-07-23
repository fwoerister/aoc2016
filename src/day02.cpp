#include <iostream>
#include <fstream>

#include "util/point.hpp"

using namespace std;

class InputParser
{
private:
    vector<string> instructions;

public:
    InputParser(string path)
    {
        ifstream f(path);
        string instruction;

        while (getline(f, instruction))
        {
            instructions.push_back(instruction);
        }

        f.close();
    }

    vector<string> getInstructions();
};

vector<string> InputParser::getInstructions()
{
    return instructions;
}

class DialPad
{
private:
    vector<string> layout;
    Point pos;

public:
    DialPad(vector<string> layout, Point start) : layout(layout), pos(start) {}

    void move(char dir);
    char getCurrentDigit();
};

void DialPad::move(char dir)
{
    switch (dir)
    {
    case 'U':
        if (layout[pos.x][pos.y - 1] != ' ')
        {
            Point offset(0, -1);
            pos = pos + offset;
        }
        break;
    case 'D':
        if (layout[pos.x][pos.y + 1] != ' ')
        {
            Point offset(0, 1);
            pos = pos + offset;
        }
        break;
    case 'L':
        if (layout[pos.x - 1][pos.y] != ' ')
        {
            Point offset(-1, 0);
            pos = pos + offset;
        }
        break;
    case 'R':
        if (layout[pos.x + 1][pos.y] != ' ')
        {
            Point offset(1, 0);
            pos = pos + offset;
        }
        break;
    }
}

char DialPad::getCurrentDigit()
{
    return layout[pos.y][pos.x];
}

int main()
{
    InputParser ip("input/day02.txt");

    vector<string> l1Layout = {
        "     ",
        " 123 ",
        " 456 ",
        " 789 ",
        "     "};

    Point l1Start(2, 2);
    DialPad l1DialPad(l1Layout, l1Start);

    vector<string> l2Layout = {
        "       ",
        "   1   ",
        "  234  ",
        " 56789 ",
        "  ABC  ",
        "   D   ",
        "       ",
    };

    Point l2Start(1, 3);
    DialPad l2DialPad(l2Layout, l2Start);

    cout << "Part 1:" << endl;

    for (string inst : ip.getInstructions())
    {
        for (char c : inst)
            l1DialPad.move(c);
        cout << l1DialPad.getCurrentDigit();
    }

    cout << endl
         << "Part 2:"
         << endl;

    for (string inst : ip.getInstructions())
    {
        for (char c : inst)
            l2DialPad.move(c);
        cout << l2DialPad.getCurrentDigit();
    }
    cout << endl;
}