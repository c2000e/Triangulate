#include "Triangulate/vector.h"

#include <cmath>
#include <iomanip>

Vector::Vector(int x, int y) : x(x), y(y) {}

Vector Vector::operator-() const
{
    return Vector(-x, -y);
}

Vector Vector::operator+(const Vector& v) const
{
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(const Vector& v) const
{
    return *this + -v;
}

Vector Vector::operator*(const int& c) const
{
    return Vector(x * c, y * c);
}

Vector Vector::operator/(const int& c) const
{
    return *this * (1 / c);
}

int Vector::sqrMagnitude() const
{
    return dot(*this, *this);
}

int dot(const Vector& a, const Vector& b)
{
    return a.x * b.x + a.y * b.y;
}

int det(const Vector& a, const Vector& b)
{
    return a.x * b.y - a.y * b.x;
}

double angle(const Vector& a, const Vector& b)
{
    double t = std::atan2(det(a, b), dot(a, b));
    if (t < 0) t += 2 * 3.14159265359;
    return t;
}

bool operator==(const Vector& a, const Vector& b)
{
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const Vector& a, const Vector& b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

// is (a) above (b)?
bool above(const Vector& a, const Vector& b)
{
    return a.y > b.y || (a.y == b.y && a.x < b.x);
}

// is (a) below (b)?
bool below(const Vector& a, const Vector& b)
{
    return a.y < b.y || (a.y == b.y && a.x > b.x);
}

// does a point (c) lie to the left of a line (a, b)?
bool left(const Vector& a, const Vector& b, const Vector& c)
{
    if (a.y < b.y) return det(b - a, c - a) > 0;
    return det(a - b, c - b) > 0;
}

// does a point (c) lie to the right of a line (a, b)?
bool right(const Vector& a, const Vector& b, const Vector& c)
{
    if (a.y < b.y) return det(b - a, c - a) < 0;
    return det(a - b, c - b) < 0;
}

// does (c) lie between (a) and (b) on the x-axis?
bool betweenX(const Vector& a, const Vector& b, const Vector& c)
{
    if (a.x < c.x != b.x < c.x) return true;
    return false;
}

// does (c) lie between (a) and (b) on the x-axis?
bool betweenY(const Vector& a, const Vector& b, const Vector& c)
{
    if (a.y < c.y != b.y < c.y) return true;
    return false;
}

// does a ray from (c) heading left hit the line segment (a, b)?
bool rayHitLeft(const Vector& a, const Vector& b, const Vector& c)
{
    if (betweenY(a, b, c) && right(a, b, c)) return true;
    return false;
}

// does a ray from (c) heading right hit the line segment (a, b)?
bool rayHitRight(const Vector& a, const Vector& b, const Vector& c)
{
    if (betweenY(a, b, c) && left(a, b, c)) return true;
    return false;
}

// is the shortest route from (a) to (b) around (c) clockwise?
bool clockwise(const Vector& a, const Vector& b, const Vector& c)
{
    Vector u = a - c;
    Vector v = b - c;

    if (u.x >= 0 && v.x < 0) return true;
    if (u.x < 0 && v.x >= 0) return false;
    if (u.x == 0 && v.x == 0.0)
    {
        if (u.y >= 0 || v.y >= 0) return u.y > v.y;
        return u.y < v.y;
    }

    int d = det(u, v);
    if (d < 0) return true;
    if (d > 0) return false;
    return u.sqrMagnitude() > v.sqrMagnitude();
}

// the x coordinate where a horizontal ray from (c) hits the line segment
// (a, b). assumes an intersection does exist.
double intersectX(const Vector& a, const Vector& b, const Vector &c)
{
    if (a.y == b.y) return a.x;
    return (b.x - a.x) / (b.y - a.y) * c.y + a.x; 
}

// the y coordinate where a vertical ray from (c) hits the line segment
// (a, b). assumes an intersection does exist.
double intersectY(const Vector& a, const Vector& b, const Vector& c)
{
    if (a.x == b.y) return a.y;
    return (b.y - a.y) / (b.x - a.x) * c.x + a.y;
}

