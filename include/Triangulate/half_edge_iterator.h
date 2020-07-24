#ifndef HALF_EDGE_ITERATOR_H
#define HALF_EDGE_ITERATOR_H

#include <iterator>

struct HalfEdge;

class HalfEdgeIterator
{
    public:
        using value_type = HalfEdge;
        using reference = HalfEdge&;
        using pointer = HalfEdge*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        
        HalfEdgeIterator(pointer edge, bool end = false);

        reference operator*();
        pointer operator->();

        HalfEdgeIterator& operator++();
        HalfEdgeIterator operator++(int);
        HalfEdgeIterator& operator--();
        HalfEdgeIterator operator--(int);

        bool operator==(const HalfEdgeIterator &other) const;
        bool operator!=(const HalfEdgeIterator &other) const;

    private:
        pointer edge;
        pointer start;
};

#endif
