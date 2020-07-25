#include "Triangulate/half_edge.h"

#include <algorithm>
#include <cmath>
#include <iterator>

HalfEdge::HalfEdge(Vertex* origin) : origin(origin), twin(nullptr),
    next(nullptr), prev(nullptr), face(nullptr), helper(nullptr) {}

HalfEdge::iterator HalfEdge::begin()
{
    return { this };
}

HalfEdge::iterator HalfEdge::end()
{
    return { this, true };
}

HalfEdge* HalfEdge::leftmost()
{
    return ::leftmost<HalfEdge::iterator>(this->begin(), this->end());
}

bool HalfEdge::interior()
{
    HalfEdge* e = this->leftmost();
    if (angle(*e->next->origin - *e->origin, *e->prev->origin - *e->origin)
            < 3.14159265359) return true;
    return false;
}

bool HalfEdge::left()
{
    int num_intersections = 0;
    HalfEdge* e = this->next;
    while (e != this)
    {
        if ((this->origin->y > e->origin->y)
            != (this->origin->y > e->twin->origin->y))
        {
            num_intersections++;
        }
        e = e->next;
    }
    if (num_intersections % 2 == 0) return false;
    return true;
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
    os << &e << " " << (Vector) *e.origin << std::endl;
    os << "\ttwin: " << e.twin << " " << (Vector) *e.twin->origin
        << std::endl;
    os << "\tnext: " << e.next << " " << (Vector) *e.next->origin
        << std::endl;
    os << "\tprev: " << e.prev << " " << (Vector) *e.prev->origin
        << std::endl;
    os << "\tface: " << e.face << std::endl;
    return os;
}

void sortClockwise(std::vector<HalfEdge*>& edges, const Vertex* center)
{
    std::sort(edges.begin(), edges.end(),
        [center](const HalfEdge* a, const HalfEdge* b)
        { return clockwise(*a->twin->origin, *b->twin->origin,
                *center); });
}

