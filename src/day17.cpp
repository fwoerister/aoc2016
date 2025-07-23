#include "util/md5.hpp"
#include <queue>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

struct Point
{
    int x, y;

    Point(int x, int y) : x(x), y(y) {}
};

struct State
{
    string prefix;
    string path;
    Point pos;

    State(string prefix, string path, Point pos) : prefix(prefix), path(path), pos(pos) {}

    bool operator==(const State &other) const
    {
        return path.length() == other.path.length();
    }

    bool operator<(const State &other) const
    {
        return path.length() < other.path.length();
    }

    bool operator<=(const State &other) const
    {
        return *this == other || *this < other;
    }

    bool operator>(const State &other) const
    {
        return !(*this == other || *this < other);
    }

    bool operator>=(const State &other) const
    {
        return !(*this < other);
    }

    bool operator!=(const State &other) const
    {
        return !(*this == other);
    }
};

bool isOpen(char c)
{
    return 'b' <= c && c <= 'f';
}

bool isValidPos(Point p)
{
    if (!(0 <= p.x && p.x < 4))
        return false;
    if (!(0 <= p.y && p.y < 4))
        return false;
    return true;
}

string findShortestPath(string prefix, Point startPoint)
{
    int longestPathLen = -1;

    State initState(prefix, "", startPoint);

    priority_queue<State, vector<State>, greater<State>> activeNodes;
    activeNodes.push(initState);

    while (activeNodes.size() > 0)
    {
        State current = activeNodes.top();
        activeNodes.pop();

        if (current.pos.x == 3 && current.pos.y == 3)
        {
            return current.path;
        }
        else
        {

            stringstream ss;
            ss << current.prefix << current.path;

            MD5Hash md5;
            md5.digestMessage(ss.str());
            string hash = md5.getHash();

            if (isOpen(hash[0]))
            {
                State newState(current);
                newState.pos.y -= 1;

                if (isValidPos(newState.pos))
                {
                    stringstream newPath;
                    newPath << newState.path << "U";
                    newState.path = newPath.str();
                    activeNodes.push(newState);
                }
            }

            if (isOpen(hash[1]))
            {
                State newState(current);
                newState.pos.y += 1;

                if (isValidPos(newState.pos))
                {
                    stringstream newPath;
                    newPath << newState.path << "D";
                    newState.path = newPath.str();
                    activeNodes.push(newState);
                }
            }

            if (isOpen(hash[2]))
            {
                State newState(current);
                newState.pos.x -= 1;

                if (isValidPos(newState.pos))
                {
                    stringstream newPath;
                    newPath << newState.path << "L";
                    newState.path = newPath.str();
                    activeNodes.push(newState);
                }
            }

            if (isOpen(hash[3]))
            {
                State newState(current);
                newState.pos.x += 1;

                if (isValidPos(newState.pos))
                {
                    stringstream newPath;
                    newPath << newState.path << "R";
                    newState.path = newPath.str();
                    activeNodes.push(newState);
                }
            }
        }
    }

    return "";
}

int findLongestPath(string prefix, Point startPoint)
{

    int longestPathLen = -1;

    State initState(prefix, "", startPoint);

    priority_queue<State, vector<State>, greater<State>> activeNodes;
    activeNodes.push(initState);

    while (activeNodes.size() > 0)
    {
        State current = activeNodes.top();
        activeNodes.pop();

        if (current.pos.x == 3 && current.pos.y == 3)
        {
            if (longestPathLen == -1 || longestPathLen < current.path.length())
            {
                longestPathLen = current.path.length();
            }
        }
        else
        {

            stringstream ss;
            ss << current.prefix << current.path;

            MD5Hash md5;
            md5.digestMessage(ss.str());
            string hash = md5.getHash();

            if (isOpen(hash[0]))
            {
                State newState(current);
                newState.pos.y -= 1;

                if (isValidPos(newState.pos))
                {
                    stringstream newPath;
                    newPath << newState.path << "U";
                    newState.path = newPath.str();
                    activeNodes.push(newState);
                }
            }

            if (isOpen(hash[1]))
            {
                State newState(current);
                newState.pos.y += 1;

                if (isValidPos(newState.pos))
                {
                    stringstream newPath;
                    newPath << newState.path << "D";
                    newState.path = newPath.str();
                    activeNodes.push(newState);
                }
            }

            if (isOpen(hash[2]))
            {
                State newState(current);
                newState.pos.x -= 1;

                if (isValidPos(newState.pos))
                {
                    stringstream newPath;
                    newPath << newState.path << "L";
                    newState.path = newPath.str();
                    activeNodes.push(newState);
                }
            }

            if (isOpen(hash[3]))
            {
                State newState(current);
                newState.pos.x += 1;

                if (isValidPos(newState.pos))
                {
                    stringstream newPath;
                    newPath << newState.path << "R";
                    newState.path = newPath.str();
                    activeNodes.push(newState);
                }
            }
        }
    }

    return longestPathLen;
}

int main()
{
    ifstream f("input/day17.txt");
    string prefix;

    getline(f, prefix);

    Point start(0, 0);
    cout << findShortestPath(prefix, start) << endl;
    cout << findLongestPath(prefix, start) << endl;
}