#include "Triangulate/half_edge_iterator.h"

#include "Triangulate/half_edge.h"

using iterator = HalfEdgeIterator;

iterator::HalfEdgeIterator(iterator::value_type edge, bool end)
    : edge(end ? nullptr : edge), start(edge) {}

iterator::reference iterator::operator*()
{
    return edge;
}

iterator::pointer iterator::operator->()
{
    return &edge;
}

iterator& iterator::operator++()
{
    edge = (edge == start->prev) ? nullptr : edge->next;
    return *this;
}

iterator iterator::operator++(int)
{
    iterator i = *this;
    edge = (edge == start->prev) ? nullptr : edge->next;
    return i;
}

iterator& iterator::operator--()
{
    edge = edge ? edge->prev : start->prev;
    return *this;
}

iterator iterator::operator--(int)
{
    iterator i = *this;
    edge = edge ? edge->prev : start->prev;
    return i;
}

bool iterator::operator==(const iterator &other) const
{
    return edge == other.edge;
}

bool iterator::operator!=(const iterator &other) const
{
    return !(*this == other);
}

