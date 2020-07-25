#ifndef HALF_EDGE_H
#define HALF_EDGE_H

#include "Triangulate/half_edge_iterator.h"

#include "Triangulate/face.h"
#include "Triangulate/vertex.h"

struct HalfEdge
{
    Vertex* origin;
    HalfEdge* twin;
    HalfEdge* next;
    HalfEdge* prev;
    Face* face;
    Vertex* helper;

    HalfEdge(Vertex* origin);

    using iterator = HalfEdgeIterator;
    iterator begin();
    iterator end();

    template<typename Iter>
    HalfEdge* leftNeighbor(Iter begin, Iter end)
    {
        HalfEdge* m = nullptr;
        double m_intersection;

        for (; begin != end; ++begin)
        {
            if (rayHitLeft(*(*begin)->origin, *(*begin)->twin->origin,
                        *this->origin))
            {
                double e_intersection = intersectX(*(*begin)->origin,
                        *(*begin)->twin->origin, *this->origin);
                if (m)
                {
                    if (e_intersection > m_intersection
                            && e_intersection < this->origin->x)
                    {
                        m = *begin;
                        m_intersection = e_intersection;
                    }
                }
                else
                {
                    m = *begin;
                    m_intersection = e_intersection;
                }
            }
        }
        return m;
    }
    
    HalfEdge* leftNeighbor()
    {
        return leftNeighbor(this->begin(), this->end());
    }

    HalfEdge* leftmost();

    bool interior();
    bool left();
};

bool operator==(const HalfEdge& a, const HalfEdge& b);
bool operator!=(const HalfEdge& a, const HalfEdge& b);

std::ostream& operator<<(std::ostream& os, const HalfEdge& e);

template <class Iter>
HalfEdge* leftmost(Iter begin, Iter end)
{
    HalfEdge* m = *begin;
    for (; begin != end; ++begin)
    {
        if ((*begin)->origin->x < m->origin->x)
        {
            m = *begin;
        }
        else if ((*begin)->origin->x == m->origin->x
                && (*begin)->origin->y < m->origin->y)
        {
            m = *begin;
        }
    }
    return m;
}

void sortClockwise(std::vector<HalfEdge*>& edges, const Vertex* center);

#endif
