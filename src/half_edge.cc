#include "Triangulate/half_edge.h"

#include <algorithm>

HalfEdge::HalfEdge(Vertex* origin) : origin(origin), twin(nullptr),
    next(nullptr), prev(nullptr), face(nullptr) {}

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

void sortClockwise(std::vector<HalfEdge*>& edges, const Vertex* center)
{
    std::sort(edges.begin(), edges.end(),
        [center](const HalfEdge* a, const HalfEdge* b)
        { return clockwise(a->twin->origin->position, b->twin->origin->position,
              center->position); });
}

const HalfEdge* lowerLeft(const HalfEdge* s)
{ 
    const HalfEdge* m = s;
    const HalfEdge* e = s->next;
    while (*e != *s)
    { 
        if (e->origin->position.x < m->origin->position.x)
        {
            m = e;
        }
        else if (e->origin->position.x == m->origin->position.x)
        {
            if (e->origin->position.y < m->origin->position.y)
            {
                m = e;
            }
        }
        e = e->next;
    }
    return m;
}

bool interior(const HalfEdge* e)
{
    e = lowerLeft(e);
    if (angle(e->prev->origin->position - e->origin->position,
            e->next->origin->position - e->origin->position)
            > 3.14159265359) return true;
    return false;
}
