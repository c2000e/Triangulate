#ifndef VERTEX_H
#define VERTEX_H

#include "Triangulate/vector.h"

struct HalfEdge;

struct Vertex
{
    Vector position;
    HalfEdge* edge;

    Vertex(double x, double y);
};

bool operator==(const Vertex& a, const Vertex& b);
bool operator!=(const Vertex& a, const Vertex& b);

std::ostream& operator<<(std::ostream& os, const Vertex& v);

#endif
