#include "Triangulate/vector.h"

#include <cmath>
#include <iomanip>

Vector::Vector(double x, double y) : x(x), y(y) {}

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

Vector Vector::operator*(const double& c) const
{
    return Vector(x * c, y * c);
}

Vector Vector::operator/(const double& c) const
{
    return *this * (1 / c);
}

double Vector::sqrMagnitude() const
{
    return dot(*this, *this);
}

double Vector::magnitude() const
{
    return std::sqrt(sqrMagnitude());
}

double Vector::direction() const
{
    double t = std::atan2(y, x);
    if (t < 0)
    {
        t += 2 * PI;
    }
    return t;
}

Vector Vector::unit() const
{
    return *this / this->magnitude();
}

double dot(const Vector& a, const Vector& b)
{
    return a.x * b.x + a.y * b.y;
}

double det(const Vector& a, const Vector& b)
{
    return a.x * b.y - a.y * b.x;
}

double angleBetween(const Vector& a, const Vector& b)
{
    double t = std::atan2(det(a, b), dot(a, b));
    if (t < 0)
    {
        t += 2 * PI;
    }
    return t;
}

static bool equal(const double& a, const double& b)
{
    if (std::abs(a - b) < 0.0000001) return true;
    return false;
}

bool operator==(const Vector& a, const Vector& b)
{
    return equal(a.x, b.x) && equal(a.y, b.y);
}

bool operator!=(const Vector& a, const Vector& b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os << "(" << std::fixed << std::setprecision(2) << v.x << ", " << v.y
        << ")" << std::endl;
    return os;
}
