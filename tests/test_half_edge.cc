#include "gtest/gtest.h"

#include "Triangulate/half_edge.h"

TEST(test_half_edge, sortEdgesCW)
{
    Vertex center(-137, 53);

    std::vector<Vertex> vertices;
    vertices.push_back(Vertex( 0 + center.position.x,
         1 + center.position.y));
    vertices.push_back(Vertex( 1 + center.position.x,
         1 + center.position.y));
    vertices.push_back(Vertex( 1 + center.position.x,
         0 + center.position.y));
    vertices.push_back(Vertex( 1 + center.position.x,
        -1 + center.position.y));
    vertices.push_back(Vertex( 0 + center.position.x,
        -1 + center.position.y));
    vertices.push_back(Vertex(-1 + center.position.x,
        -1 + center.position.y));
    vertices.push_back(Vertex(-1 + center.position.x,
         0 + center.position.y));
    vertices.push_back(Vertex(-1 + center.position.x,
         1 + center.position.y));

    std::vector<HalfEdge> edges;
    for (int i = 0; i < vertices.size(); i++)
    {
        HalfEdge e;
        e.origin = &center;
        HalfEdge t;
        t.origin = &vertices[i];
        edges.push_back(e);
        edges.push_back(t);
    }
    for (int i = 0; i < edges.size(); i += 2)
    {
        edges[i].twin = &edges[i + 1];
        edges[i + 1].twin = &edges[i];
    }
   
    std::vector<HalfEdge*> edgePointers;
    for (int i = 0; i < edges.size(); i++)
    {
        edgePointers.push_back(&edges[i]);
    }

    std::vector<HalfEdge*> shuffledEdgePointers;
    shuffledEdgePointers.push_back(edgePointers[8]);
    shuffledEdgePointers.push_back(edgePointers[14]);
    shuffledEdgePointers.push_back(edgePointers[2]);
    shuffledEdgePointers.push_back(edgePointers[0]);
    shuffledEdgePointers.push_back(edgePointers[10]);
    shuffledEdgePointers.push_back(edgePointers[6]);
    shuffledEdgePointers.push_back(edgePointers[4]);
    shuffledEdgePointers.push_back(edgePointers[12]);

    sortEdgesCW(shuffledEdgePointers, &center);

    for (int i = 0; i < edgePointers.size(); i += 2)
    {
        ASSERT_EQ(edgePointers[i], shuffledEdgePointers[i / 2]);
    }
}

