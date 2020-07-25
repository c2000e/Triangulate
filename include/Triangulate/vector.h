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
double angle(const Vector& a, const Vector& b);

bool operator==(const Vector& a, const Vector& b);
bool operator!=(const Vector& a, const Vector& b);

std::ostream& operator<<(std::ostream& os, const Vector& v);

bool above(const Vector& a, const Vector& b);
bool below(const Vector& a, const Vector& b);
bool left(const Vector& a, const Vector& b, const Vector& c);
bool right(const Vector& a, const Vector& b, const Vector& c);
bool betweenX(const Vector& a, const Vector& b, const Vector& c);
bool betweenY(const Vector& a, const Vector& b, const Vector& c);
bool rayHitLeft(const Vector& a, const Vector& b, const Vector& c);
bool rayHitRight(const Vector& a, const Vector& b, const Vector& c);
bool clockwise(const Vector& a, const Vector& b, const Vector& c);

double intersectX(const Vector& a, const Vector& b, const Vector& c);
double intersectY(const Vector& a, const Vector& b, const Vector& c);

#endif
