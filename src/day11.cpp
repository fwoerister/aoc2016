#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <string>

#include <functional>

using namespace std;

struct Component
{
    string type;
    string element;

    Component(string type, string element) : type(type), element(element) {}

    bool operator==(const Component &other) const
    {
        return type == other.type && element == other.element;
    }

    bool operator!=(const Component &other) const
    {
        return !(*this == other);
    }

    bool operator<(const Component &other) const
    {
        if (type == other.type)
        {
            return element < other.element;
        }

        return type < other.type;
    }
};

class State
{
private:
    vector<set<Component>> floors;
    int elevator;
    int steps;
    int estimate;

public:
    State(vector<set<Component>> floors) : floors(floors), elevator(0), steps(0) {}

    int getElevator()
    {
        return elevator;
    }

    set<Component> getCurrentFloor()
    {
        return floors[elevator];
    }

    set<Component> getFloor(int floor)
    {
        return floors[floor];
    }

    void increaseSteps()
    {
        steps += 1;
    }

    int getSteps()
    {
        return steps;
    }

    int getEstimate() const
    {
        int estimate = steps;

        estimate += (floors[0].size() / 2) * 3;
        estimate += floors[1].size();
        estimate += (floors[2].size() / 2);

        return estimate;
    }

    bool isGoalState()
    {
        for (int i = 0; i < 3; i++)
            if (floors[i].size() != 0)
                return false;
        return true;
    }

    bool move(set<Component> payload, int targetFloor)
    {
        if (abs(elevator - targetFloor) != 1)
            return false;

        if (targetFloor < 0 || targetFloor >= 4)
            return false;

        if (payload.size() == 0 || payload.size() > 2)
            return false;

        for (Component c : payload)
        {
            floors[elevator].erase(c);
            floors[targetFloor].insert(c);
        }

        elevator = targetFloor;

        return isValid();
    }

    bool isValid()
    {
        for (auto floor : floors)
        {
            for (auto c : floor)
            {
                if (c.type == "m")
                {
                    Component counterPart("g", c.element);
                    bool isUnprotected = floor.find(counterPart) == floor.end();
                    int generatorCount = 0;
                    for (auto c : floor)
                        if (c.type == "g")
                            generatorCount++;
                    if (isUnprotected && generatorCount > 0)
                        return false;
                }
            }
        }
        return true;
    }

    string toString() const
    {
        stringstream s;
        s << "E:" << elevator << endl;

        map<string, string> alias;

        int inc = 0;

        for (int i = 3; i >= 0; --i)
        {
            for (Component c : floors[i])
            {
                if (alias.find(c.element) == alias.end())
                    alias[c.element] = to_string(++inc);
            }
        }

        for (int i = 3; i >= 0; --i)
        {
            s << "F" << i + 1 << ":";
            for (Component c : floors[i])
                s << "<" << c.type << " " << alias[c.element] << ">";
            s << endl;
        }

        return s.str();
    }

    bool operator==(const State &other) const
    {
        return getEstimate() == other.getEstimate();
    }

    bool operator!=(const State &other) const
    {
        return !(*this != other);
    }

    bool operator<(const State &other) const
    {
        return getEstimate() < other.getEstimate();
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

class PuzzleSolver
{
private:
    priority_queue<State, vector<State>, greater<State>> activeStates;
    set<string> visited;

    bool isVisitedState(State &s)
    {
        return visited.find(s.toString()) != visited.end();
    }

public:
    PuzzleSolver(State initState)
    {
        activeStates.push(initState);
        visited.insert(initState.toString());
    }

    int solve()
    {
        int steps = -1;
        while (steps == -1 && activeStates.size() != 0)
        {
            State current = activeStates.top();
            activeStates.pop();
            vector<State> expandedNodes = expand(current);

            for (State newState : expandedNodes)
            {
                if (newState.isGoalState())
                    steps = newState.getSteps();
                else
                {
                    activeStates.push(newState);
                    visited.insert(newState.toString());
                }
            }
        }

        return steps;
    }

    vector<State> expand(State s)
    {
        vector<State> expandedNodes;

        set<Component> currentFloor = s.getCurrentFloor();

        vector<Component> components;

        for (Component c : s.getCurrentFloor())
            components.push_back(c);

        for (int i = 0; i < components.size(); i++)
        {
            for (int j = i; j < components.size(); j++)
            {
                Component c1 = components[i];
                Component c2 = components[j];
                if (c1.type != c2.type && c1.element != c2.element)
                    continue;

                set<Component> payload;

                payload = {c1,
                           c2};

                State newStateUp(s);
                if (newStateUp.move(payload, s.getElevator() + 1) && !isVisitedState(newStateUp))
                {
                    newStateUp.increaseSteps();
                    expandedNodes.push_back(newStateUp);
                }

                State newStateDown(s);
                if (newStateDown.move(payload, newStateDown.getElevator() - 1) && !isVisitedState(newStateDown))
                {
                    newStateDown.increaseSteps();
                    expandedNodes.push_back(newStateDown);
                }
            }
        }

        return expandedNodes;
    }
};

void parseFloor(string floorString, set<Component> &floor)
{
    regex mRegex("(\\w+)-compatible microchip");
    regex gRegex("(\\w+) generator");

    auto mItBegin = sregex_iterator(floorString.begin(), floorString.end(), mRegex);
    auto mItEnd = sregex_iterator();

    while (mItBegin != mItEnd)
    {
        Component c("m", (*mItBegin)[1]);
        floor.insert(c);
        mItBegin++;
    }

    auto gItBegin = sregex_iterator(floorString.begin(), floorString.end(), gRegex);
    auto gItEnd = sregex_iterator();

    while (gItBegin != gItEnd)
    {
        Component c("g", (*gItBegin)[1]);
        floor.insert(c);
        gItBegin++;
    }
}

int main()
{
    ifstream f("input/day11.txt");
    string line;

    vector<set<Component>> floorsP1;

    for (int i = 0; i < 4; ++i)
    {
        getline(f, line);
        set<Component> floor;
        parseFloor(line, floor);
        floorsP1.push_back(floor);
    }

    vector<set<Component>> floorsP2(floorsP1);

    floorsP2[0].insert(Component("g", "elerium"));
    floorsP2[0].insert(Component("g", "dilithium"));
    floorsP2[0].insert(Component("m", "elerium"));
    floorsP2[0].insert(Component("m", "dilithium"));

    State initStateP1(floorsP1);
    PuzzleSolver solverP1(initStateP1);
    cout << solverP1.solve() << endl;

    State initStateP2(floorsP2);
    PuzzleSolver solverP2(initStateP2);
    cout << solverP2.solve() << endl;
}