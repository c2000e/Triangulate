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

        std::vector<HalfEdge*> findEdges(const Vertex* v) const;
        void mergeEdge(Vertex* v, HalfEdge* e) const;

    public:
        Vertex* addVertex(int x, int y);
        HalfEdge* addEdge(int x1, int y1, int x2, int y2);
        void createFaces();

        friend std::ostream& operator<<(std::ostream& os, const Mesh& m);

        template<class T>
        friend void draw(const Mesh& m, T renderer);
};

#endif
