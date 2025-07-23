#include <iostream>
#include <sstream>

#include "point.hpp"

Point::Point() : x(0), y(0) {}

Point::Point(int x, int y) : x(x), y(y) {}

string Point::to_string()
{
    stringstream ss;

    ss << x << ", " << y;

    return ss.str();
}

int Point::getCityBlockDistance()
{
    return abs(x) + abs(y);
}

bool Point::operator==(const Point &other) const
{
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point &other) const
{
    return !(*this == other);
}

bool Point::operator<(const Point &other) const
{
    if (x == other.x)
        return y < other.y;
    return x < other.x;
}

bool Point::operator>(const Point &other) const
{
    return !(*this < other || *this == other);
}

bool Point::operator<=(const Point &other) const
{
    return *this < other || *this == other;
}
bool Point::operator>=(const Point &other) const
{
    return !(*this < other);
}

Point Point::operator+(const Point &other) const
{
    return Point(x + other.x, y + other.y);
}
