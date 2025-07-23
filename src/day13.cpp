#include <iostream>
#include <queue>
#include <set>

using namespace std;

struct Point
{
    int x, y;

    Point(int x, int y) : x(x), y(y) {}

    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point &other) const
    {
        return !(*this == other);
    }

    bool operator<(const Point &other) const
    {
        if (x == other.x)
        {
            return y < other.y;
        }
        return x < other.x;
    }

    bool operator<=(const Point &other) const
    {
        return *this == other || *this < other;
    }

    bool operator>(const Point &other) const
    {
        return !(*this == other || *this < other);
    }

    bool operator>=(const Point &other) const
    {
        return !(*this < other);
    }
};

struct State
{
    int steps;
    Point pos;

    State(int steps, Point pos) : steps(steps), pos(pos) {}

    bool operator<(const State &other) const
    {
        return steps < other.steps;
    }

    bool operator==(const State &other) const
    {
        return steps == other.steps;
    }

    bool operator!=(const State &other) const
    {
        return !(*this == other);
    }

    bool operator<=(const State &other) const
    {
        return *this < other || *this == other;
    }

    bool operator>(const State &other) const
    {
        return !(*this < other || *this == other);
    }

    bool operator>=(const State &other) const
    {
        return !(*this < other);
    }
};

class Grid
{
private:
    int secret;

public:
    Grid(int secret) : secret(secret) {}

    bool isWall(int x, int y)
    {
        Point p(x, y);
        return isWall(p);
    }

    bool isWall(Point pos)
    {
        int x = pos.x;
        int y = pos.y;

        if (x < 0 || y < 0)
            return true;

        int sum = x * x + 3 * x + 2 * x * y + y + y * y + secret;
        int oneCount = 0;

        while (sum != 0)
        {
            if (sum % 2 == 1)
                ++oneCount;
            sum = sum >> 1;
        }
        return oneCount % 2 == 1;
    }

    int shortestPath(Point start, Point end)
    {
        State s(0, start);
        set<Point> visited = {start};
        priority_queue<State, vector<State>, greater<State>> openNodes;
        openNodes.push(s);

        while (openNodes.size() != 0)
        {
            State next = openNodes.top();
            openNodes.pop();

            if (next.pos == end)
                return next.steps;

            Point leftNeighbour(next.pos.x + 1, next.pos.y);
            Point rightNeighbour(next.pos.x - 1, next.pos.y);
            Point topNeighbour(next.pos.x, next.pos.y - 1);
            Point bottomNeighbour(next.pos.x, next.pos.y + 1);

            vector<Point> neighbours = {leftNeighbour,
                                        rightNeighbour,
                                        topNeighbour,
                                        bottomNeighbour};

            for (Point n : neighbours)
                if (visited.find(n) == visited.end() && !isWall(n))
                {
                    State newState(next);
                    newState.steps = newState.steps + 1;
                    newState.pos = n;
                    openNodes.push(newState);
                    visited.insert(n);
                }
        }
        return -1;
    }

    int findReachableDestinations(Point start, int steps)
    {
        State s(0, start);
        set<Point> visited = {start};
        priority_queue<State, vector<State>, greater<State>> openNodes;
        openNodes.push(s);

        while (openNodes.size() != 0)
        {
            State next = openNodes.top();
            openNodes.pop();

            if (next.steps == steps)
                return visited.size();

            Point leftNeighbour(next.pos.x + 1, next.pos.y);
            Point rightNeighbour(next.pos.x - 1, next.pos.y);
            Point topNeighbour(next.pos.x, next.pos.y - 1);
            Point bottomNeighbour(next.pos.x, next.pos.y + 1);

            vector<Point> neighbours = {leftNeighbour,
                                        rightNeighbour,
                                        topNeighbour,
                                        bottomNeighbour};

            for (Point n : neighbours)
                if (visited.find(n) == visited.end() && !isWall(n))
                {
                    State newState(next);
                    newState.steps = newState.steps + 1;
                    newState.pos = n;
                    openNodes.push(newState);
                    visited.insert(n);
                }
        }
        return -1;
    }
};

int main()
{
    Grid g(1350);

    Point start(1, 1);
    Point end(31, 39);

    cout << g.shortestPath(start, end) << endl;

    cout << g.findReachableDestinations(start, 50) << endl;
}