#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

class Triangle
{
private:
    int x, y, z;

public:
    Triangle(int x, int y, int z) : x(x), y(y), z(z) {}

    bool isValid();
};

bool Triangle::isValid()
{
    if (x + y <= z)
        return false;
    if (y + z <= x)
        return false;
    if (z + x <= y)
        return false;

    return true;
}

class InputParserP1
{
private:
    vector<Triangle> triangles = {};

public:
    InputParserP1(string path)
    {
        ifstream f(path);
        string triangle;

        while (getline(f, triangle))
        {
            regex r("(\\d+)");
            vector<int> vals = {};

            auto val_begin = sregex_iterator(triangle.begin(), triangle.end(), r);

            while (!(*val_begin).empty())
            {
                vals.push_back(stoi((*val_begin).str()));
                val_begin++;
            }

            Triangle t(vals[0], vals[1], vals[2]);
            triangles.push_back(t);
        }
    }

    vector<Triangle> getTriangles();
};

vector<Triangle> InputParserP1::getTriangles()
{
    return triangles;
}

class InputParserP2
{
private:
    vector<Triangle> triangles;

public:
    InputParserP2(string path)
    {
        ifstream f(path);
        string triangleStr;

        vector<int> t1_vals = {};
        vector<int> t2_vals = {};
        vector<int> t3_vals = {};

        while (getline(f, triangleStr))
        {
            regex r("(\\d+)");
            auto it = sregex_iterator(triangleStr.begin(), triangleStr.end(), r);

            t1_vals.push_back(stoi((*it).str()));
            it++;
            t2_vals.push_back(stoi((*it).str()));
            it++;
            t3_vals.push_back(stoi((*it).str()));

            if (t1_vals.size() == 3)
            {
                Triangle t1(t1_vals[0], t1_vals[1], t1_vals[2]);
                triangles.push_back(t1);

                Triangle t2(t2_vals[0], t2_vals[1], t2_vals[2]);
                triangles.push_back(t2);

                Triangle t3(t3_vals[0], t3_vals[1], t3_vals[2]);
                triangles.push_back(t3);

                t1_vals.clear();
                t2_vals.clear();
                t3_vals.clear();
            }
        }
    }

    vector<Triangle> getTriangles();
};

vector<Triangle> InputParserP2::getTriangles()
{
    return triangles;
}

int main()
{
    InputParserP1 ip1("input/day03.txt");
    InputParserP2 ip2("input/day03.txt");

    int validTriangles = 0;

    for (Triangle t : ip1.getTriangles())
        if (t.isValid())
            ++validTriangles;

    cout << "Part 1:\n";
    cout << validTriangles << "\n";

    validTriangles = 0;

    for (Triangle t : ip2.getTriangles())
        if (t.isValid())
            ++validTriangles;

    cout << "Part 2:\n";
    cout << validTriangles << "\n";
}