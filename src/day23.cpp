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
    ifstream f("input/day23.txt");
    string line;

    vector<unique_ptr<Instruction>> program;

    regex r(R"((\w+) (a|b|c|d|-?\d+) ?(a|b|c|d|-?\d+)?)");
    smatch m;

    while (getline(f, line))
    {
        regex_search(line, m, r);

        if (m[1] == "cpy")
            program.push_back(make_unique<CpyInstruction>(m[2], m[3]));
        else if (m[1] == "inc")
            program.push_back(make_unique<IncInstruction>(m[2]));
        else if (m[1] == "dec")
            program.push_back(make_unique<DecInstruction>(m[2]));
        else if (m[1] == "jnz")
            program.push_back(make_unique<JnzInstruction>(m[2], m[3]));
        else if (m[1] == "tgl")
            program.push_back(make_unique<ToggleInstruction>(m[2]));
    }

    Emulator e(program);
    e.setRegisterVal("a", 7);

    while (e.getRegisterVal("pc") < program.size())
    {
        e.step();
    }

    cout << e.getRegisterVal("a") << endl;

    /*
     *  Part 2 was solved by manually analyzing the assembunny code!
     */
}