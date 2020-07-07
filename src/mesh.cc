#include "Triangulate/mesh.h"

#include <algorithm>
#include <iterator>

Vertex* Mesh::addVertex(double x, double y)
{
    Vertex v(x, y);

    // check if vertex already exists
    std::list<Vertex>::iterator vIter =
        std::find(vertices.begin(), vertices.end(), v);
    if (vIter != vertices.end()) return &(*vIter);

    // add new vertex
    vertices.push_back(v);
    return &vertices.back();
}

