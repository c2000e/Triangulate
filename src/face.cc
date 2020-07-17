#include "Triangulate/face.h"

#include "Triangulate/half_edge.h"

Face::Face() : edge(nullptr) {}

bool operator==(const Face& a, const Face& b)
{
    if (*a.edge == *b.edge) return true;

    HalfEdge* bStart = b.edge;
    HalfEdge* bCurr = bStart->next;
    while (bCurr != bStart)
    {
        if (*a.edge == *b.edge) return true;
        bCurr = bCurr->next;
    }
    return false;
}

bool operator!=(const Face& a, const Face& b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const Face& f)
{
    os << &f << std::endl;
    os << "\tedge: " << f.edge << " " << f.edge->origin->position << std::endl;
    return os;
}
