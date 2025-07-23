#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

class Map
{
private:
    std::vector<std::vector<char>> grid;
    int width;
    int height;

public:
    Map(int width, int height) : width(width), height(height)
    {
        grid.resize(width, std::vector<char>(height, ' '));
    }

    void set(int x, int y, char value)
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return;
        grid[x][y] = value;
    }

    char get(int x, int y) const
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return ' ';
        return grid[x][y];
    }

    void addRectangle(int width, int height)
    {
        for (int x = 0; x < width; ++x)
            for (int y = 0; y < height; ++y)
                grid[x][y] = 'x';
    }

    void rotateColumn(int column)
    {
        char last = grid[column][height - 1];

        for (int y = height - 2; y >= 0; --y)
            grid[column][y + 1] = grid[column][y];

        grid[column][0] = last;
    }

    void rotateRow(int row)
    {
        char last = grid[width - 1][row];

        for (int x = width - 2; x >= 0; --x)
        {
            grid[x + 1][row] = grid[x][row];
        }

        grid[0][row] = last;
    }

    void print()
    {
        cout << "---" << '\n';
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
                cout << grid[x][y];
            cout << '\n';
        }
    }

    int count()
    {
        int count = 0;
        for (int x = 0; x < width; ++x)
            for (int y = 0; y < height; ++y)
                if (grid[x][y] == 'x')
                    ++count;
        return count;
    }
};

bool startsWith(string str, string prefix)
{
    if (prefix.length() > str.length())
        return false;

    for (int i = 0; i < prefix.length(); ++i)
        if (str[i] != prefix[i])
            return false;

    return true;
}

int main()
{
    Map m(50, 6);

    ifstream f("input/day08.txt");
    string line;

    while (getline(f, line))
    {
        if (startsWith(line, "rect"))
        {
            regex regExp("(\\d+)x(\\d+)");
            smatch match;

            regex_search(line, match, regExp);

            m.addRectangle(stoi(match[1]), stoi(match[2]));
        }
        else if (startsWith(line, "rotate column"))
        {
            regex regExp("(\\d+) by (\\d+)");
            smatch match;

            regex_search(line, match, regExp);

            for (int i = 0; i < stoi(match[2]); ++i)
                m.rotateColumn(stoi(match[1]));
        }
        else if (startsWith(line, "rotate row"))
        {
            regex regExp("(\\d+) by (\\d+)");
            smatch match;

            regex_search(line, match, regExp);

            for (int i = 0; i < stoi(match[2]); ++i)
                m.rotateRow(stoi(match[1]));
        }
    }

    cout << "Part 1:" << endl;
    cout << m.count() << endl;

    cout << "Part 2:" << endl;
    m.print();
}