#ifndef VECTOR_H
#define VECTOR_H

const double PI = 3.14159265358979323846;

struct Vector
{
    double x, y;

    Vector(double x, double y);

    Vector operator-() const;  

    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(const double& c) const;
    Vector operator/(const double& c) const;

    double sqrMagnitude() const;
    double magnitude() const;
    double direction() const;

    Vector unit() const;
};

double dot(const Vector& a, const Vector& b);
double det(const Vector& a, const Vector& b);
double angleBetween(const Vector& a, const Vector& b);

bool operator==(const Vector& a, const Vector& b);
bool operator!=(const Vector& a, const Vector& b);

#endif
