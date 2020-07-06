#ifndef MESH_H
#define MESH_H

#include "Triangulate/half_edge.h"

#include <list>

class Mesh
{
    private:
        std::list<Vertex> vertices;
        std::list<HalfEdge> edges;
        std::list<Face> faces;

    public:
        Vertex* addVertex(double x, double y);
        HalfEdge* addEdge(double x1, double y1, double x2, double y2);
        void createFaces();

        friend std::ostream& operator<<(std::ostream& os, const Mesh& m);

        template<class T>
        friend void draw(const Mesh& m, T renderer);
};

#endif
