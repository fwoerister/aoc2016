#include <iostream>

using namespace std;

#pragma once

class Emulator;

class Instruction
{
public:
    virtual void executeOn(Emulator &e);
    virtual unique_ptr<Instruction> toggle();
};

class CpyInstruction : public Instruction
{
private:
    string x;
    string y;

public:
    CpyInstruction(string x, string y);
    void executeOn(Emulator &e) override;
    unique_ptr<Instruction> toggle() override;
};

class IncInstruction : public Instruction
{
private:
    string x;

public:
    IncInstruction(string x);
    void executeOn(Emulator &e) override;
    unique_ptr<Instruction> toggle() override;
};

class DecInstruction : public Instruction
{
private:
    string x;

public:
    DecInstruction(string x);
    void executeOn(Emulator &e) override;
    unique_ptr<Instruction> toggle() override;
};

class JnzInstruction : public Instruction
{
private:
    string x;
    string y;

public:
    JnzInstruction(string x, string y);
    void executeOn(Emulator &e) override;
    unique_ptr<Instruction> toggle() override;
};

class ToggleInstruction : public Instruction
{
private:
    string x;

public:
    ToggleInstruction(string x);
    void executeOn(Emulator &e) override;
    unique_ptr<Instruction> toggle() override;
};

class OutInstruction : public Instruction
{
private:
    string x;

public:
    OutInstruction(string x);
    void executeOn(Emulator &e) override;
    unique_ptr<Instruction> toggle() override;
};