#include <iostream>
#include <fstream>
#include <set>
#include "util/point.hpp"

using namespace std;

class DirectionParser
{
public:
    vector<string> dirTokens;

    DirectionParser(string path)
    {
        ifstream f(path);
        string token;

        while (getline(f, token, ','))
        {
            token = DirectionParser::trimToken(token);
            if (token.length() > 0)
                dirTokens.push_back(token);
        }

        f.close();
    }

    static string trimToken(string token)
    {
        int idx = 0;

        while (idx < token.length() && isspace(token[idx]))
            ++idx;

        token.erase(0, idx);

        idx = token.length() - 1;

        while (idx > 0 && isspace(token[idx]))
            --idx;

        token.erase(idx + 1, token.length() - idx);
        return token;
    }
};

class MapPosition
{
public:
    Point p;
    char orientation = 'n';
    vector<Point> path;

    void turnLeft();
    void turnRight();
    void move(int distance);

    Point getFirstCrossing();
};

void MapPosition::turnLeft()
{
    switch (orientation)
    {
    case 'n':
        orientation = 'w';
        break;
    case 'w':
        orientation = 's';
        break;
    case 's':
        orientation = 'e';
        break;
    case 'e':
        orientation = 'n';
        break;
    }
}

void MapPosition::turnRight()
{
    switch (orientation)
    {
    case 'n':
        orientation = 'e';
        break;
    case 'e':
        orientation = 's';
        break;
    case 's':
        orientation = 'w';
        break;
    case 'w':
        orientation = 'n';
        break;
    }
}

void MapPosition::move(int distance)
{
    Point offset;

    switch (orientation)
    {
    case 'n':
        for (int i = p.y; i > p.x - distance; --i)
        {
            Point newPoint = {p.x, i};
            path.push_back(newPoint);
        }

        offset = Point(0, -distance);
        p = p + offset;
        break;
    case 'e':
        for (int i = p.x; i < p.x + distance; ++i)
        {
            Point newPoint = {i, p.y};
            path.push_back(newPoint);
        }

        offset = Point(distance, 0);
        p = p + offset;
        break;
    case 's':
        for (int i = p.y; i < p.y + distance; ++i)
        {
            Point newPoint = {p.x, i};
            path.push_back(newPoint);
        }

        offset = Point(0, distance);
        p = p + offset;
        break;
    case 'w':
        for (int i = p.x; i > p.x - distance; --i)
        {
            Point newPoint = {i, p.y};
            path.push_back(newPoint);
        }

        offset = Point(-distance, 0);
        p = p + offset;
        break;
    }
}

Point MapPosition::getFirstCrossing()
{
    set<Point> visited = {};

    for (Point current : path)
    {
        if (visited.count(current) != 0)
        {
            return current;
        }

        visited.insert(current);
    }

    return Point(-1, -1);
}

int main()
{
    DirectionParser dp("input/day01.txt");
    MapPosition pos;

    for (string tkn : dp.dirTokens)
    {
        if (tkn[0] == 'R')
            pos.turnRight();
        else
            pos.turnLeft();

        tkn.erase(0, 1);
        pos.move(stoi(tkn));
    }

    cout << "Level 1:\n";
    cout << pos.p.getCityBlockDistance() << "\n\n";

    cout
        << "Level 2:\n";
    Point hq = pos.getFirstCrossing();
    cout << hq.getCityBlockDistance() << '\n';
}