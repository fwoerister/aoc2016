
#include <map>
#include <vector>
#include <memory>

#pragma once

using namespace std;

class Instruction;

class Emulator
{
private:
    map<string, int> registers;
    vector<unique_ptr<Instruction>> &program;
    vector<int> output;

public:
    Emulator(vector<unique_ptr<Instruction>> &program);

    void incPC();

    int getRegisterVal(string reg);

    void setRegisterVal(string reg, int val);

    void step();

    void toggleInstructionAt(int address);

    void print(int val);

    int getOutputSize();

    bool isClock();
};