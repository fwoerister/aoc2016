#include "instructions.hpp"
#include "emulator.hpp"

using namespace std;

void Instruction::executeOn(Emulator &e)
{
    e.incPC();
}

unique_ptr<Instruction> Instruction::toggle()
{
    return make_unique<Instruction>(*this);
}

CpyInstruction::CpyInstruction(string x, string y) : x(x), y(y) {}

void CpyInstruction::executeOn(Emulator &e)
{
    Instruction::executeOn(e);

    int val = 0;

    if (x == "a" || x == "b" || x == "c" || x == "d")
        val = e.getRegisterVal(x);
    else
        val = stoi(x);

    if (y == "a" || y == "b" || y == "c" || y == "d")
        e.setRegisterVal(y, val);
}

unique_ptr<Instruction> CpyInstruction::toggle()
{
    return make_unique<JnzInstruction>(x, y);
}

IncInstruction::IncInstruction(string x) : x(x) {}

void IncInstruction::executeOn(Emulator &e)
{
    Instruction::executeOn(e);
    e.setRegisterVal(x, e.getRegisterVal(x) + 1);
}

unique_ptr<Instruction> IncInstruction::toggle()
{
    return make_unique<DecInstruction>(x);
}

DecInstruction::DecInstruction(string x) : x(x) {}

void DecInstruction::executeOn(Emulator &e)
{
    Instruction::executeOn(e);

    e.setRegisterVal(x, e.getRegisterVal(x) - 1);
}

unique_ptr<Instruction> DecInstruction::toggle()
{
    return make_unique<IncInstruction>(x);
}

JnzInstruction::JnzInstruction(string x, string y) : x(x), y(y) {}

void JnzInstruction::executeOn(Emulator &e)
{
    int val_x, val_y;
    if (x == "a" || x == "b" || x == "c" || x == "d")
        val_x = e.getRegisterVal(x);
    else
        val_x = stoi(x);

    if (y == "a" || y == "b" || y == "c" || y == "d")
        val_y = e.getRegisterVal(y);
    else
        val_y = stoi(y);

    if (val_x != 0)
        e.setRegisterVal("pc", e.getRegisterVal("pc") + val_y);
    else
        Instruction::executeOn(e);
}

unique_ptr<Instruction> JnzInstruction::toggle()
{
    return make_unique<CpyInstruction>(x, y);
}

ToggleInstruction::ToggleInstruction(string x) : x(x) {}

void ToggleInstruction::executeOn(Emulator &e)
{
    int val;
    if (x == "a" || x == "b" || x == "c" || x == "d")
        val = e.getRegisterVal(x);
    else
        val = stoi(x);

    e.toggleInstructionAt(e.getRegisterVal("pc") + val);

    Instruction::executeOn(e);
}

unique_ptr<Instruction> ToggleInstruction::toggle()
{
    return make_unique<IncInstruction>(x);
}

OutInstruction::OutInstruction(string x) : x(x) {}

void OutInstruction::executeOn(Emulator &e)
{
    int val;
    if (x == "a" || x == "b" || x == "c" || x == "d")
        val = e.getRegisterVal(x);
    else
        val = stoi(x);

    e.print(val);

    Instruction::executeOn(e);
}

unique_ptr<Instruction> OutInstruction::toggle()
{
    return make_unique<IncInstruction>(x);
}