#include "Triangulate/vertex.h"

#include <iomanip>

Vertex::Vertex(double x, double y) : position(x, y), edge(nullptr) {}

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
