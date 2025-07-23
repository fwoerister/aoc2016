#include <iostream>
#include <map>
#include <fstream>
#include <regex>

#include <memory>

#include "util/emulator.hpp"
#include "util/instructions.hpp"

using namespace std;

int main()
{
    ifstream f("input/day12.txt");
    string line;

    vector<unique_ptr<Instruction>> program;

    regex r(R"((\w+) (a|b|c|d|-?\d+) ?(a|b|c|d|-?\d+)?)");
    smatch m;

    while (getline(f, line))
    {
        regex_search(line, m, r);

        if (m[1] == "cpy")
        {
            program.push_back(make_unique<CpyInstruction>(m[2], m[3]));
        }
        else if (m[1] == "inc")
        {
            program.push_back(make_unique<IncInstruction>(m[2]));
        }
        else if (m[1] == "dec")
        {
            program.push_back(make_unique<DecInstruction>(m[2]));
        }
        else if (m[1] == "jnz")
        {
            program.push_back(make_unique<JnzInstruction>(m[2], m[3]));
        }
    }

    Emulator e(program);

    while (e.getRegisterVal("pc") < program.size())
    {
        e.step();
    }

    cout << e.getRegisterVal("a") << endl;

    e.setRegisterVal("pc", 0);
    e.setRegisterVal("c", 1);

    while (e.getRegisterVal("pc") < program.size())
    {
        e.step();
    }

    cout << e.getRegisterVal("a") << endl;
}