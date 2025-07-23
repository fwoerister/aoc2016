#include <iostream>
#include <fstream>
#include <map>
#include <regex>

using namespace std;

class Room
{
private:
    string name;
    map<char, int> charStat;
    string checksum;
    int sectorId;

    char getNextChecksumChar()
    {
        map<char, int>::iterator it;
        char next = '-';
        int count = 0;

        for (it = charStat.begin(); it != charStat.end(); it++)
        {
            char key = (*it).first;
            int freq = (*it).second;

            if (next == '-' || freq > count)
            {
                next = key;
                count = freq;
            }
            else if (count == freq && key < next)
            {
                next = (*it).first;
                count = (*it).second;
            }
        }

        charStat.erase(next);
        return next;
    }

public:
    Room(string name, string checksum, int sectorId) : name(name), checksum(checksum), sectorId(sectorId)
    {
        for (char c : name)
            if (c != '-')
            {
                if (charStat.count(c) == 0)
                {
                    charStat[c] = 1;
                }
                else
                {
                    charStat[c] += 1;
                }
            }
    }

    string calcChecksum();

    string decryptName();

    bool isValid();

    void print();

    int getSectorId();
};

string Room::decryptName()
{
    int alphaLen = int('z') - int('a') + 1;

    string decrypted = "";

    for (char c : name)
    {
        if (c == '-')
        {
            decrypted += " ";
        }
        else
        {
            int offset = c - 'a';
            offset = (offset + sectorId) % alphaLen;
            decrypted += char('a' + offset);
        }
    }

    return decrypted;
}

int Room::getSectorId()
{
    return sectorId;
}

string Room::calcChecksum()
{
    string checksum = "";

    while (checksum.length() < 5)
    {
        checksum = checksum + getNextChecksumChar();
    }

    return checksum;
}

void Room::print()
{
    cout << name << " " << checksum << "\n";
}

bool Room::isValid()
{
    string correctChecksum = calcChecksum();
    if (checksum != correctChecksum)
    {
        return false;
    }
    return true;
}

class InputParser
{
private:
    vector<Room> rooms;

public:
    InputParser(string path)
    {
        ifstream f(path);
        string roomStr;

        while (getline(f, roomStr))
        {
            regex nameReg("([a-z-]+)");
            auto nameIt = sregex_iterator(roomStr.begin(), roomStr.end(), nameReg);

            regex checksumReg("\\[([a-z]+)\\]");
            auto checksumIt = sregex_iterator(roomStr.begin(), roomStr.end(), checksumReg);
            string checksum = (*checksumIt).str();

            regex sectorIdReg("(\\d+)");
            auto sectorIdIt = sregex_iterator(roomStr.begin(), roomStr.end(), sectorIdReg);
            int sectorId = stoi((*sectorIdIt).str());

            Room r((*nameIt).str(), checksum.substr(1, checksum.length() - 2), sectorId);
            rooms.push_back(r);
        }
    }

    vector<Room> getRooms();
};

vector<Room> InputParser::getRooms()
{
    return rooms;
}

int main()
{
    InputParser ip("input/day04.txt");

    cout << "Part 1:" << endl;

    int sum = 0;

    for (Room r : ip.getRooms())
    {
        if (r.isValid())
            sum += r.getSectorId();
    }

    cout << sum << endl;

    cout << "Part 2:" << endl;
    for (Room r : ip.getRooms())
    {
        string decryptedName = r.decryptName();
        if (decryptedName.find("northpole") != string::npos)
            cout << r.getSectorId() << endl;
    }
}