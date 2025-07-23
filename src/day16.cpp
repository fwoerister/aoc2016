#include <iostream>
#include <sstream>

using namespace std;

string expandData(string data, int minLength)
{
    stringstream ss;

    ss << data;

    ss << '0';

    for (int idx = data.length() - 1; idx >= 0; --idx)
    {
        if (data[idx] == '0')
        {
            ss << '1';
        }
        else
        {
            ss << '0';
        }
    }

    if (ss.str().length() >= minLength)
        return ss.str().substr(0, minLength);
    else
        return expandData(ss.str(), minLength);
}

string getChecksum(string data)
{
    stringstream ss;

    for (int idx = 0; idx < data.length(); idx += 2)
    {
        if (data[idx] == data[idx + 1])
            ss << '1';
        else
            ss << '0';
    }

    if (ss.str().length() % 2 == 0)
    {
        return getChecksum(ss.str());
    }

    return ss.str();
}

int main()
{
    string data = "01110110101001000";

    cout << getChecksum(expandData(data, 272)) << endl;
    cout << getChecksum(expandData(data, 35651584)) << endl;
}