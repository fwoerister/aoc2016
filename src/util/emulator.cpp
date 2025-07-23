#include "emulator.hpp"
#include "instructions.hpp"

#include <map>
#include <vector>

using namespace std;

Emulator::Emulator(vector<unique_ptr<Instruction>> &program) : program(program)
{
    registers["a"] = 0;
    registers["b"] = 0;
    registers["c"] = 0;
    registers["d"] = 0;
    registers["pc"] = 0;
}

void Emulator::incPC()
{
    registers["pc"] += 1;
}

int Emulator::getRegisterVal(string reg)
{
    return registers[reg];
}

void Emulator::setRegisterVal(string reg, int val)
{
    registers[reg] = val;
}

void Emulator::step()
{
    program[registers["pc"]].get()->executeOn(*this);
}

void Emulator::toggleInstructionAt(int address)
{
    if (address >= program.size())
        return;

    program[address] = program[address].get()->toggle();
}

void Emulator::print(int val)
{
    output.push_back(val);
}

int Emulator::getOutputSize()
{
    return output.size();
}

bool Emulator::isClock()
{
    for (int i = 0; i < output.size(); i++)
    {
        if (i % 2 == 0 && output[i] != 0)
            return false;
        else if (i % 2 == 1 && output[i] != 1)
            return false;
    }

    return true;
}