#ifndef CYCLE_H
#define CYCLE_H

#include "Triangulate/half_edge.h"

struct Cycle
{
    std::vector<HalfEdge*> edges;
    Cycle* parent;

    Cycle();

    void findParent(std::vector<Cycle>& cycles);
    Cycle* root();

    Vertex* lowerLeftVertex() const;
    HalfEdge* lowerLeftEdge() const;

    bool isFace() const;
};

#endif
