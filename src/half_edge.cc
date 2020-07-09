#include "Triangulate/half_edge.h"

#include <algorithm>

HalfEdge::HalfEdge() : origin(nullptr), twin(nullptr), next(nullptr),
    prev(nullptr), face(nullptr) {}

void sortEdgesCW(std::vector<HalfEdge*>& edges, const Vertex* center)
{
    std::sort(edges.begin(), edges.end(),
        [center](const HalfEdge* a, const HalfEdge* b)
        { return cwLess(a->twin->origin->position, b->twin->origin->position,
              center->position); });
}

bool operator==(const HalfEdge& a, const HalfEdge& b)
{
    return *a.origin == *b.origin && *a.twin->origin == *b.twin->origin;
}

bool operator!=(const HalfEdge& a, const HalfEdge& b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const HalfEdge& e)
{
    os << &e << " " << e.origin->position << std::endl;
    os << "\ttwin: " << e.twin << " " << e.twin->origin->position << std::endl;
    os << "\tnext: " << e.next << " " << e.next->origin->position << std::endl;
    os << "\tprev: " << e.prev << " " << e.prev->origin->position << std::endl;
    os << "\tface: " << e.face << std::endl;
    return os;
}
