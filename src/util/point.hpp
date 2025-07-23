#include <string>

using namespace std;

struct Point
{
    int x, y;

    Point();

    Point(int x, int y);

    string to_string();

    int getCityBlockDistance();

    bool operator==(const Point &other) const;

    bool operator!=(const Point &other) const;

    bool operator<(const Point &other) const;

    bool operator>(const Point &other) const;

    bool operator<=(const Point &other) const;

    bool operator>=(const Point &other) const;

    Point operator+(const Point &other) const;
};