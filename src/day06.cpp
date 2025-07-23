#include <iostream>
#include <map>
#include <sstream>
#include <fstream>

using namespace std;

class RepeatingMessageSignal
{
private:
    vector<map<char, int>> posFreqs;

public:
    RepeatingMessageSignal(int size)
    {
        for (int i = 0; i < size; ++i)
        {
            map<char, int> freqMap;
            posFreqs.push_back(freqMap);
        }
    }

    void digestMessage(string msg);
    char getMostFrequentLetterAt(int pos);
    char getLeastFrequentLetterAt(int pos);
    string extractP1Message();
    string extractP2Message();
};

void RepeatingMessageSignal::digestMessage(string msg)
{
    for (int i = 0; i < msg.length(); ++i)
    {
        if (posFreqs[i].count(msg[i]) == 0)
        {
            posFreqs[i][msg[i]] = 1;
        }
        else
        {
            posFreqs[i][msg[i]] += 1;
        }
    }
}

char RepeatingMessageSignal::getMostFrequentLetterAt(int pos)
{
    char letter = ' ';
    uint32_t freq = 0;

    for (const auto &pair : posFreqs[pos])
        if (posFreqs[pos][pair.first] > freq)
        {
            letter = pair.first;
            freq = posFreqs[pos][pair.first];
        }

    return letter;
}

char RepeatingMessageSignal::getLeastFrequentLetterAt(int pos)
{
    char letter = ' ';
    uint32_t freq = -1;

    for (const auto &pair : posFreqs[pos])
        if (posFreqs[pos][pair.first] < freq)
        {
            letter = pair.first;
            freq = posFreqs[pos][pair.first];
        }

    return letter;
}

string RepeatingMessageSignal::extractP1Message()
{
    stringstream msgStream;

    for (int i = 0; i < posFreqs.size(); ++i)
    {
        msgStream << getMostFrequentLetterAt(i);
    }

    return msgStream.str();
}

string RepeatingMessageSignal::extractP2Message()
{
    stringstream msgStream;

    for (int i = 0; i < posFreqs.size(); ++i)
    {
        msgStream << getLeastFrequentLetterAt(i);
    }

    return msgStream.str();
}

int main()
{
    ifstream f("input/day06.txt");
    string line;

    RepeatingMessageSignal rms(8);

    while (getline(f, line))
    {
        rms.digestMessage(line);
    }

    f.close();

    cout << "Part 1:" << endl;
    cout << rms.extractP1Message() << endl;
    cout << "Part 2:" << endl;
    cout << rms.extractP2Message() << endl;
}