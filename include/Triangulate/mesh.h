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
        Vertex* addVertex(int x, int y);
        HalfEdge* addEdge(int x1, int y1, int x2, int y2);
        HalfEdge* addEdge(Vertex* v1, Vertex* v2);
        void createFaces();
        void triangulate();

        friend std::ostream& operator<<(std::ostream& os, const Mesh& m);

        template<class T>
        friend void draw(const Mesh& m, T renderer);
};

#endif
