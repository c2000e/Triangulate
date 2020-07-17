#ifndef HALF_EDGE_H
#define HALF_EDGE_H

#include "Triangulate/face.h"
#include "Triangulate/vertex.h"

struct HalfEdge
{
    Vertex* origin;
    HalfEdge* twin;
    HalfEdge* next;
    HalfEdge* prev;
    Face* face;

    HalfEdge();
};

void sortEdgesCW(std::vector<HalfEdge*>& edges, const Vertex* center);

bool operator==(const HalfEdge& a, const HalfEdge& b);
bool operator!=(const HalfEdge& a, const HalfEdge& b);

std::ostream& operator<<(std::ostream& os, const HalfEdge& e);

const HalfEdge* lowerLeft(const HalfEdge* e);
bool interior(const HalfEdge* e);

#endif
