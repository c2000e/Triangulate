#include "Triangulate/vertex.h"

#include "Triangulate/half_edge.h"

#include <iomanip>

Vertex::Vertex(int x, int y) : position(x, y), edge(nullptr) {}

std::vector<HalfEdge*> Vertex::edges() const
{
    std::vector<HalfEdge*> edges;
    if (edge)
    {
        edges.push_back(edge);
        HalfEdge* e = edge->twin->next;
        while (e != edge)
        {
            edges.push_back(e);
            e = e->twin->next;
        }
    }
    return edges;
}

void Vertex::mergeEdge(HalfEdge* e)
{
    std::vector<HalfEdge*> edges = this->edges();
    edges.push_back(e);
    if (edges.size() > 1)
    {
        sortClockwise(edges, this);
        for (int i = 0; i < edges.size() - 1; i++)
        {
            edges[i]->twin->next = edges[i + 1];
            edges[i + 1]->prev = edges[i]->twin;
        }
        edges.back()->twin->next = edges.front();
        edges.front()->prev = edges.back()->twin;
    }
    else
    {
        e->twin->next = e;
        e->prev = e->twin;
    }
    edge = edges.front();
}

bool operator==(const Vertex& a, const Vertex& b)
{
    return a.position == b.position;
}

bool operator!=(const Vertex& a, const Vertex& b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
    os << &v << " " << v.position;
    return os;
}
