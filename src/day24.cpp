#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <set>
#include <map>

#include "util/point.hpp"

using namespace std;

struct State
{
    Point pos;
    int steps;
    set<Point> path;

    State(Point pos, int steps) : pos(pos), steps(steps) {}

    bool operator==(const State &other) const
    {
        return steps == other.steps;
    }

    bool operator!=(const State &other) const
    {
        return !(*this == other);
    }

    bool operator<(const State &other) const
    {
        return steps < other.steps;
    }

    bool operator>(const State &other) const
    {
        return !(*this < other || *this == other);
    }

    bool operator<=(const State &other) const
    {
        return *this < other || *this == other;
    }
    bool operator>=(const State &other) const
    {
        return !(*this < other);
    }
};

class Map
{
private:
    vector<string> m;
    map<string, int> cache;

public:
    Map(vector<string> m) : m(m) {}

    char getVal(Point pos)
    {
        return m[pos.y][pos.x];
    }

    Point find(char c)
    {
        for (int x = 0; x < m[0].length(); x++)
            for (int y = 0; y < m.size(); y++)
                if (getVal(Point(x, y)) == c)
                    return Point(x, y);
        return Point(-1, -1);
    }

    vector<Point> getNeighbours(Point p)
    {
        Point top(p.x, p.y - 1);
        Point bottom(p.x, p.y + 1);
        Point left(p.x - 1, p.y);
        Point right(p.x + 1, p.y);

        vector<Point> neighbours;

        if (top.y >= 0 && getVal(top) != '#')
            neighbours.push_back(top);

        if (bottom.y < m.size() && getVal(bottom) != '#')
            neighbours.push_back(bottom);

        if (left.x >= 0 && getVal(left) != '#')
            neighbours.push_back(left);

        if (right.x < m[0].length() && getVal(right) != '#')
            neighbours.push_back(right);

        return neighbours;
    }

    int shortest_path(char start, char end)
    {
        stringstream ss;
        ss << start << end;

        if (cache.count(ss.str()) != 0)
        {
            return cache.at(ss.str());
        }

        Point startPoint = find(start);
        Point endPoint = find(end);

        priority_queue<State, vector<State>, greater<State>> openStates;
        openStates.push(State(startPoint, 0));

        set<Point> visitedPositions;
        visitedPositions.insert(startPoint);

        while (openStates.size() > 0)
        {
            State current = openStates.top();
            openStates.pop();

            if (current.pos == endPoint)
            {
                cache.insert(pair<string, int>(ss.str(), current.steps));
                return current.steps;
            }

            for (Point n : getNeighbours(current.pos))
            {
                State newState(current);
                newState.steps += 1;
                newState.pos = n;
                newState.path.insert(n);

                if (visitedPositions.find(n) == visitedPositions.end())
                {
                    visitedPositions.insert(n);
                    openStates.push(newState);
                }
            }
        }

        return -1;
    }

    int shortest_route(set<char> spots, set<char> visited, char current, bool returnToOrigin)
    {
        int minSteps = -1;
        for (char next : spots)
        {
            if (visited.count(next) == 0 && next != current)
            {
                set<char> nextVisited(visited);
                nextVisited.insert(next);
                int candidate = shortest_path(current, next) + shortest_route(spots, nextVisited, next, returnToOrigin);

                if (minSteps == -1)
                {
                    minSteps = candidate;
                }
                else if (candidate < minSteps)
                {
                    minSteps = candidate;
                }
            }
        }

        if (visited.size() == spots.size())
            if (returnToOrigin)
                return shortest_path(current, '0');
            else
                return 0;
        else
            return minSteps;
    }

    void print(set<Point> path)
    {
        for (int y = 0; y < m.size(); y++)
        {
            for (int x = 0; x < m[0].length(); x++)
            {
                if (path.count(Point(x, y)) == 0)
                {
                    cout << m[y][x];
                }
                else
                {
                    cout << 'X';
                }
            }
            cout << endl;
        }
    }
};

Map parseMap(string path)
{
    ifstream f(path);
    string line;

    vector<string> lines;

    while (getline(f, line))
        lines.push_back(line.substr(0, line.length() - 1));

    return Map(lines);
}

int main()
{
    Map m = parseMap("input/day24.txt");

    set<char> spots = {'1', '2', '3', '4', '5', '6', '7'};
    set<char> visited;

    cout << m.shortest_route(spots, visited, '0', false) << endl;

    cout << m.shortest_route(spots, visited, '0', true) << endl;
}