#ifndef HALF_EDGE_ITERATOR_H
#define HALF_EDGE_ITERATOR_H

#include <iterator>

struct HalfEdge;

class HalfEdgeIterator
{
    public:
        using value_type = HalfEdge*;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        
        HalfEdgeIterator(value_type edge, bool end = false);

        reference operator*();
        pointer operator->();

        HalfEdgeIterator& operator++();
        HalfEdgeIterator operator++(int);
        HalfEdgeIterator& operator--();
        HalfEdgeIterator operator--(int);

        bool operator==(const HalfEdgeIterator &other) const;
        bool operator!=(const HalfEdgeIterator &other) const;

    private:
        value_type edge;
        value_type start;
};

#endif
