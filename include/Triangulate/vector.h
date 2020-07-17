#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

struct Vector
{
    int x, y;

    Vector(int x, int y);

    Vector operator-() const;  

    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(const int& c) const;
    Vector operator/(const int& c) const;

    int sqrMagnitude() const;
};

int dot(const Vector& a, const Vector& b);
int det(const Vector& a, const Vector& b);

bool operator==(const Vector& a, const Vector& b);
bool operator!=(const Vector& a, const Vector& b);

std::ostream& operator<<(std::ostream& os, const Vector& v);

bool cwLess(const Vector& a, const Vector& b, const Vector& c);

#endif
