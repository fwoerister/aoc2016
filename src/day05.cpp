#include <iostream>
#include <cstdint>
#include <bit>
#include <bitset>
#include <sstream>

#include "util/md5.hpp"

using namespace std;

bool isPasswordHash(string hash)
{

    for (int i = 0; i < 5; ++i)
    {
        if (hash[i] != '0')
        {
            return false;
        }
    }

    return true;
}

bool isValidPassword(string pwd)
{
    for (char c : pwd)
        if (c == ' ')
            return false;
    return true;
}

bool isValidDigit(char c)
{
    string digits = "01234567";

    for (char d : digits)
        if (c == d)
            return true;
    return false;
}

int main()
{
    int id = 1;

    string pwd = "        ";

    int pwdIdx = 0;
    while (!isValidPassword(pwd))
    {
        string hash, tag;
        do
        {
            MD5Hash md5;
            stringstream roomTag;
            roomTag << "wtnhxymk" << id;
            tag = roomTag.str();
            md5.digestMessage(tag);
            ++id;
            hash = md5.getHash();

        } while (!isPasswordHash(hash));

        pwd[pwdIdx++] = hash[5];
        cout << pwd << endl;
    }

    cout << "Part 1:" << endl;
    cout << pwd << endl;

    id = 1;
    pwd = "        ";

    while (!isValidPassword(pwd))
    {
        string hash, tag;
        do
        {
            MD5Hash md5;
            stringstream roomTag;
            roomTag << "wtnhxymk" << id;
            tag = roomTag.str();
            md5.digestMessage(tag);
            ++id;
            hash = md5.getHash();

        } while (!isPasswordHash(hash));

        if (isValidDigit(hash[5]))
        {
            int pos = stoi(string(1, hash[5]));
            if (pwd[pos] == ' ')
            {
                pwd[pos] = hash[6];
                cout << pwd << endl;
            }
        }
    }

    cout << "Part 2: " << endl;
    cout << pwd << endl;
}