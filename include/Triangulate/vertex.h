#ifndef VERTEX_H
#define VERTEX_H

#include "Triangulate/vector.h"

#include <vector>

struct HalfEdge;

struct Vertex
{
    Vector position;
    HalfEdge* edge;

    Vertex(int x, int y);

    std::vector<HalfEdge*> edges() const;
    void mergeEdge(HalfEdge* e);
};

bool operator==(const Vertex& a, const Vertex& b);
bool operator!=(const Vertex& a, const Vertex& b);

std::ostream& operator<<(std::ostream& os, const Vertex& v);

#endif
