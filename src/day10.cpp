#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <regex>

using namespace std;

regex VAL_REGEX("value (\\d+) goes to bot (\\d+)");
regex PASS_REGEX("bot (\\d+) gives low to (bot|output) (\\d+) and high to (bot|output) (\\d+)");

class FactoryComponent
{
public:
    virtual void recieve(int chip) {}
    virtual void print() {}
};

class Output : public FactoryComponent
{
private:
    vector<int> chips;

public:
    void recieve(int chip)
    {
        chips.push_back(chip);
    }

    void print()
    {
        for (int i : chips)
            cout << i << " ";
        cout << endl;
    }

    int getFactor()
    {
        int factor = 1;
        for (int val : chips)
            factor *= val;
        return factor;
    }
};

class Bot : public FactoryComponent
{
private:
    int lowVal, highVal;
    FactoryComponent *low, *high;

public:
    Bot() : lowVal(-1), highVal(-1) {}
    Bot(int lowVal, int highVal) : lowVal(lowVal), highVal(highVal) {}

    void recieve(int chip)
    {

        if (highVal != -1)
        {
            return;
        }

        if (lowVal == -1)
        {
            lowVal = chip;
        }
        else
        {
            if (lowVal < chip)
            {
                highVal = chip;
            }
            else
            {
                highVal = lowVal;
                lowVal = chip;
            }

            low->recieve(lowVal);
            high->recieve(highVal);
        }
    }

    void setLow(FactoryComponent *b)
    {
        low = b;
    }

    void setHigh(FactoryComponent *b)
    {
        high = b;
    }

    int getLowVal()
    {
        return lowVal;
    }

    int getHighVal()
    {
        return highVal;
    }

    void print()
    {
        cout << "lowVal: " << lowVal << endl;
        cout << "highVal: " << highVal << endl;
    }
};

class BotFactory
{
public:
    static map<int, Bot> bots;

    static Bot &get(int id)
    {
        if (bots.count(id) == 0)
        {
            Bot b;
            bots[id] = b;
        }
        return bots[id];
    }
};

map<int, Bot> BotFactory::bots;

class OutputFactory
{
private:
    static map<int, Output> outputs;

public:
    static Output &get(int id)
    {
        if (outputs.count(id) == 0)
        {
            Output o;
            outputs[id] = o;
        }

        return outputs[id];
    }
};

map<int, Output> OutputFactory::outputs;

int main()
{

    map<int, vector<int>> initVals;

    ifstream f("input/day10.txt");
    string line;

    while (getline(f, line))
    {
        smatch m;
        if (regex_match(line, m, VAL_REGEX))
        {
            regex_search(line, m, VAL_REGEX);
            int bot = stoi(m[2]);
            int val = stoi(m[1]);

            if (initVals.count(bot) == 0)
            {
                vector<int> vals = {val};
                initVals[bot] = vals;
            }
            else
            {
                initVals[bot].push_back(val);
            }
        }
        else
        {
            regex_search(line, m, PASS_REGEX);

            int sourceId = stoi(m[1]);
            int lowId = stoi(m[3]);
            int highId = stoi(m[5]);

            Bot &source = BotFactory::get(sourceId);

            if (m[2] == "bot")
                source.setLow(&(BotFactory::get(lowId)));
            else if (m[2] == "output")
                source.setLow(&(OutputFactory::get(lowId)));

            if (m[4] == "bot")
                source.setHigh(&(BotFactory::get(highId)));
            else if (m[2] == "output")
                source.setHigh(&(OutputFactory::get(highId)));
        }
    }

    for (auto &entry : initVals)
    {
        for (int val : entry.second)
            BotFactory::get(entry.first).recieve(val);
    }

    for (int i = 0; i < 200; i++)
        if (BotFactory::get(i).getLowVal() == 17 && BotFactory::get(i).getHighVal() == 61)
            cout << i << endl;

    cout << OutputFactory::get(0).getFactor() * OutputFactory::get(1).getFactor() * OutputFactory::get(2).getFactor() << endl;
}