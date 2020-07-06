#ifndef FACE_H
#define FACE_H

#include <iostream>
#include <vector>

struct HalfEdge;

struct Face
{
    HalfEdge* edge;
    std::vector<HalfEdge*> holes;

    Face();
};

bool operator==(const Face& a, const Face& b);
bool operator!=(const Face& a, const Face& b);

std::ostream& operator<<(std::ostream& os, const Face& f);

#endif
