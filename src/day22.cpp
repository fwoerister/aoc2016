#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <set>
#include <sstream>

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
        if (y == other.y)
            return x < other.x;
        return y < other.y;
    }
};

struct Node
{
    Point pos;
    int size, avail, used, ratio;

    Node(Point pos, int size, int used, int avail, int ratio) : pos(pos), size(size), used(used), avail(avail), ratio(ratio) {}

    bool operator==(const Node &other) const
    {
        return pos == other.pos;
    }

    bool operator!=(const Node &other) const
    {
        return !(*this == other);
    }

    bool operator<(const Node &other) const
    {
        return pos < other.pos;
    }

    bool operator<=(const Node &other) const
    {
        return *this == other || *this < other;
    }

    bool operator>(const Node &other) const
    {
        return !(*this == other || *this < other);
    }

    bool operator>=(const Node &other) const
    {
        return !(*this < other);
    }
};

struct State
{
    int steps;
    int width, height;
    Point emptyNode;
    Point goalData;
    vector<Node> grid;

    State(int steps, vector<Node> grid, Point goalData) : steps(steps), grid(grid), emptyNode(0, 0), goalData(goalData)
    {
        if (grid.size() > 0)
        {
            width = grid[grid.size() - 1].pos.x + 1;
            height = grid[grid.size() - 1].pos.y + 1;
        }
        else
        {
            width = 0;
            height = 0;
        }

        for (Node n : grid)
            if (n.used == 0)
                emptyNode = n.pos;
    }

    void copyData(Point src, Point dest)
    {
        grid[dest.y * width + dest.x].used += getNode(src).used;
        grid[dest.y * width + dest.x].avail -= getNode(src).used;

        grid[src.y * width + src.x].used = 0;
        grid[src.y * width + src.x].avail = grid[src.y * width + src.x].size;
    }

    Node getNode(int x, int y) const
    {
        return grid[y * width + x];
    }

    Node getNode(Point pos)
    {
        return getNode(pos.x, pos.y);
    }

    vector<Node> getNeighbours(Point p)
    {
        vector<Node> neighbours;
        if (p.x > 0)
            neighbours.push_back(getNode(p.x - 1, p.y));

        if (p.x < width - 1)
            neighbours.push_back(getNode(p.x + 1, p.y));

        if (p.y > 0)
            neighbours.push_back(getNode(p.x, p.y - 1));

        if (p.y < height - 1)
            neighbours.push_back(getNode(p.x, p.y + 1));

        return neighbours;
    }

    Node getEmptyNode() const
    {
        return getNode(emptyNode.x, emptyNode.y);
    }

    char getPosChar(int x, int y)
    {
        int minUsed = -1;

        if (x == 0 && y == 0)
            return 'A';

        if (getNode(x, y).used == 0)
            return '*';

        if (x == width - 1 && y == 0)
            return 'O';
        if (getNode(x, y).ratio >= 90)
            return '#';
        else
            return '.';
    }

    string toString()
    {
        stringstream ss;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                ss << '|' << getNode(x, y).used << ' ' << getNode(x, y).avail;
            }
            ss << endl;
        }

        return ss.str();
    }

    int getEstimate() const
    {
        int estimate = abs(emptyNode.x - (goalData.x - 1));
        estimate += abs(emptyNode.y - goalData.y);

        estimate += (goalData.x - 1) * 5 + 1;
        estimate += goalData.y;

        return steps + estimate;
    }

    bool operator==(const State &other) const
    {
        return getEstimate() == other.getEstimate();
    }

    bool operator!=(const State &other) const
    {
        return !(*this == other);
    }

    bool operator<(const State &other) const
    {
        return getEstimate() < other.getEstimate();
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
};

struct VisitState
{
    Point emptyNode;
    Point goalData;

    VisitState(State s) : emptyNode(s.emptyNode), goalData(s.goalData) {}

    bool operator==(const VisitState &other) const
    {
        return emptyNode == other.emptyNode && goalData == other.goalData;
    }

    bool operator!=(const VisitState &other) const
    {
        return !(*this == other);
    }

    bool operator<(const VisitState &other) const
    {
        if (emptyNode == other.emptyNode)
            return goalData < other.goalData;
        return emptyNode < other.emptyNode;
    }
};

State findSolution(State init)
{
    priority_queue<State, vector<State>, greater<State>> activeNodes;
    activeNodes.push(init);

    VisitState initVisitState(init);

    set<VisitState> visited = {initVisitState};

    while (activeNodes.size() > 0)
    {
        State current = activeNodes.top();
        activeNodes.pop();

        if (current.goalData == Point(0, 0))
        {
            return current;
        }

        Node emptyNode = current.getEmptyNode();

        for (Node n : current.getNeighbours(emptyNode.pos))
        {
            State newState(current);

            if (emptyNode.size >= n.used)
            {
                newState.steps += 1;
                newState.copyData(n.pos, emptyNode.pos);
                newState.emptyNode = n.pos;

                if (n.pos == newState.goalData)
                    newState.goalData = emptyNode.pos;

                VisitState vs(newState);

                if (visited.find(vs) == visited.end())
                {
                    visited.insert(vs);
                    activeNodes.push(newState);
                }
            }
        }
    }

    return State(-1, vector<Node>{}, init.goalData);
}

vector<Node> parseNodes(string filename)
{
    ifstream f(filename);
    string line;

    vector<Node> nodes;

    while (getline(f, line))
    {
        regex r("/dev/grid/node-x(\\d+)-y(\\d+) +(\\d+)T +(\\d+)T +(\\d+)T +(\\d+)%");
        smatch m;

        if (regex_match(line, r))
        {
            regex_search(line, m, r);

            Point p(stoi(m[1]), stoi(m[2]));
            Node n(p, stoi(m[3]), stoi(m[4]), stoi(m[5]), stoi(m[6]));
            nodes.push_back(n);
        }
    }

    return nodes;
}

int main()
{
    vector<Node> nodes = parseNodes("input/day22.txt");

    int pairCount = 0;

    for (Node n1 : nodes)
        for (Node n2 : nodes)
            if (n1 != n2 && n1.used <= n2.avail && n1.used != 0)
                pairCount++;

    cout << pairCount << endl;

    sort(nodes.begin(), nodes.end());
    State s(0, nodes, Point(31, 0));

    State prepedState = findSolution(s);

    cout << prepedState.steps << endl;
}