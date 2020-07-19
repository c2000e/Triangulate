#include "gtest/gtest.h"

#include "Triangulate/half_edge.h"

#include "Triangulate/mesh.h"

TEST(test_half_edge, leftmost)
{
    Mesh m;

    HalfEdge* e1 = m.addEdge(1, 1, 0, 0);
    HalfEdge* e2 = m.addEdge(0, 0, 0, 1);
    HalfEdge* e3 = m.addEdge(0, 1, 1, 1);

    ASSERT_EQ(e1->leftmost(), e2);
    ASSERT_EQ(e2->leftmost(), e2);
    ASSERT_EQ(e3->leftmost(), e2);
}

TEST(test_half_edge, interior)
{
    Mesh m;

    HalfEdge* e1 = m.addEdge(1, 1, 0, 0);
    HalfEdge* e2 = m.addEdge(0, 0, 0, 1);
    HalfEdge* e3 = m.addEdge(0, 1, 1, 1);

    ASSERT_FALSE(e1->interior());
    ASSERT_FALSE(e2->interior());
    ASSERT_FALSE(e3->interior());
    ASSERT_TRUE(e1->twin->interior());
    ASSERT_TRUE(e2->twin->interior());
    ASSERT_TRUE(e3->twin->interior());
}

TEST(test_half_edge, sortClockwise)
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
        HalfEdge e(&center);
        HalfEdge t(&vertices[i]);
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

    sortClockwise(shuffledEdgePointers, &center);

    for (int i = 0; i < edgePointers.size(); i += 2)
    {
        ASSERT_EQ(edgePointers[i], shuffledEdgePointers[i / 2]);
    }
}

