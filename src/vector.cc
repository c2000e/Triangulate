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
    os << "(" << v.x << ", " << v.y << ")" << std::endl;
    return os;
}

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
