#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <regex>
#include <memory>
#include <set>

using namespace std;

class Instruction
{
public:
    virtual string scramble(string input) { return input; }
    virtual string reverse(string input) { return input; }
};

class SwapPosInst : public Instruction
{
private:
    int x, y;

public:
    SwapPosInst(int x, int y) : x(x), y(y) {}

    string scramble(string input) override
    {
        char tmp;
        tmp = input[x];
        input[x] = input[y];
        input[y] = tmp;
        return input;
    }

    string reverse(string input) override
    {
        return scramble(input);
    }
};

class SwapLetterInst : public Instruction
{
private:
    char x, y;

public:
    SwapLetterInst(char x, char y) : x(x), y(y) {}

    string scramble(string input) override
    {
        stringstream ss;

        for (char c : input)
        {
            if (c == x)
            {
                ss << y;
            }
            else if (c == y)
            {
                ss << x;
            }
            else
            {
                ss << c;
            }
        }

        return ss.str();
    }

    string reverse(string input) override
    {
        return scramble(input);
    }
};

class Rotate : public Instruction
{
private:
    char direction;
    int offset;

public:
    Rotate(char direction, int offset) : direction(direction), offset(offset) {}

    string scramble(string input) override
    {
        stringstream ss;

        offset = offset % input.length();

        if (direction == 'l')
        {
            ss << input.substr(offset, input.length() - offset);
            ss << input.substr(0, offset);
        }
        else if (direction == 'r')
        {
            ss << input.substr(input.length() - offset, offset);
            ss << input.substr(0, input.length() - offset);
        }

        return ss.str();
    }

    string reverse(string input) override
    {
        char reverseDir = direction == 'r' ? 'l' : 'r';
        Rotate reverseInst(reverseDir, offset);
        return reverseInst.scramble(input);
    }
};

class RotateBasedOnLetter : public Instruction
{
private:
    char letter;

public:
    RotateBasedOnLetter(char letter) : letter(letter) {}

    string scramble(string input) override
    {
        int offset = input.find(letter);

        if (offset >= 4)
            offset++;

        Rotate instruction('r', offset + 1);

        return instruction.scramble(input);
    }

    string reverse(string input) override
    {
        // TODO
        return input;
    }
};

class Reverse : public Instruction
{
private:
    int x, y;

public:
    Reverse(int x, int y) : x(x), y(y) {}

    string scramble(string input) override
    {
        stringstream ss;

        for (int idx = 0; idx < x; ++idx)
            ss << input[idx];

        if (y >= input.length())
            for (int idx = input.length() - 1; idx >= x; --idx)
                ss << input[idx];
        else
            for (int idx = y; idx >= x; --idx)
                ss << input[idx];

        for (int idx = y + 1; idx < input.length(); ++idx)
            ss << input[idx];

        return ss.str();
    }
};

class Move : public Instruction
{
private:
    int x, y;

public:
    Move(int x, int y) : x(x), y(y) {}

    string scramble(string input) override
    {
        stringstream ss;

        int printedIdx;
        for (int idx = 0; idx < input.length(); ++idx)
        {
            if (idx == y && x >= y)
                ss << input[x];
            if (idx != x)
                ss << input[idx];
            if (idx == y && x < y)
                ss << input[x];
        }

        return ss.str();
    }
};

vector<unique_ptr<Instruction>> parseInstructions(string filename)
{
    ifstream f(filename);
    string line;

    regex swapPosRegex("swap position (\\d+) with position (\\d+)");
    regex swapLetterRegex("swap letter (\\w) with letter (\\w)");
    regex rotateRegex("rotate (\\w+) (\\d+) steps?");
    regex rotateBasedRegex("rotate based on position of letter (\\w)");
    regex reverseRegex("reverse positions (\\d+) through (\\d+)");
    regex moveRegex("move position (\\d+) to position (\\d+)");

    smatch m;
    vector<unique_ptr<Instruction>> instructions;

    while (getline(f, line))
    {
        if (regex_match(line, swapPosRegex))
        {
            regex_search(line, m, swapPosRegex);
            instructions.push_back(make_unique<SwapPosInst>(stoi(m[1]), stoi(m[2])));
        }
        else if (regex_match(line, swapLetterRegex))
        {
            regex_search(line, m, swapLetterRegex);
            instructions.push_back(make_unique<SwapLetterInst>(m[1].str()[0], m[2].str()[0]));
        }
        else if (regex_match(line, rotateRegex))
        {
            regex_search(line, m, rotateRegex);
            instructions.push_back(make_unique<Rotate>(m[1].str()[0], stoi(m[2])));
        }
        else if (regex_match(line, rotateBasedRegex))
        {
            regex_search(line, m, rotateBasedRegex);
            instructions.push_back(make_unique<RotateBasedOnLetter>(m[1].str()[0]));
        }
        else if (regex_match(line, reverseRegex))
        {
            regex_search(line, m, reverseRegex);
            instructions.push_back(make_unique<Reverse>(stoi(m[1]), stoi(m[2])));
        }
        else if (regex_match(line, moveRegex))
        {
            regex_search(line, m, moveRegex);
            instructions.push_back(make_unique<Move>(stoi(m[1]), stoi(m[2])));
        }
        else
        {
            cout << line << endl;
        }
    }
    return instructions;
}

string encrypt(vector<unique_ptr<Instruction>> &instructions, string p)
{
    // cout << "try: " << p << endl;
    string pwd(p);
    for (int idx = 0; idx < instructions.size(); idx++)
    {
        pwd = instructions[idx].get()->scramble(pwd);
    }

    return pwd;
}

string bruteForce(vector<unique_ptr<Instruction>> &instructions, string scrambled, string chars)
{
    for (char c1 : chars)
    {
        for (char c2 : chars)
        {
            for (char c3 : chars)
            {
                for (char c4 : chars)
                {
                    for (char c5 : chars)
                    {
                        for (char c6 : chars)
                        {
                            for (char c7 : chars)
                            {
                                for (char c8 : chars)
                                {
                                    stringstream pwd;
                                    pwd << c1 << c2 << c3 << c4 << c5 << c6 << c7 << c8;
                                    if (encrypt(instructions, pwd.str()) == scrambled)
                                        return pwd.str();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return "";
}

int main()
{
    vector<unique_ptr<Instruction>> instructions = parseInstructions("input/day21.txt");

    string data = "abcdefgh";

    for (int idx = 0; idx < instructions.size(); idx++)
    {
        data = instructions[idx].get()->scramble(data);
    }

    cout << data << endl;

    cout << bruteForce(instructions, "fbgdceah", "abcdefgh") << endl;
}