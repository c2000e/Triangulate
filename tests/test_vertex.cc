#include "gtest/gtest.h"

#include "Triangulate/vertex.h"

#include "Triangulate/mesh.h"

TEST(test_vertex, edges)
{
    Mesh m;

    HalfEdge* e1 = m.addEdge(0, 0, 0, 1);
    HalfEdge* e2 = m.addEdge(0, 0, 1, 0);

    Vertex* v1 = e1->origin;
    Vertex* v2 = e1->twin->origin;
    Vertex* v3 = e2->twin->origin;

    std::vector<HalfEdge*> v1_edges = v1->edges();
    ASSERT_EQ(v1_edges.size(), 2);
    ASSERT_TRUE(v1_edges.front() == e1 || v1_edges.front() == e2);
    ASSERT_TRUE(v1_edges.back() == e1 || v1_edges.back() == e2);
    ASSERT_NE(v1_edges.front(), v1_edges.back());

    ASSERT_EQ(v2->edges().size(), 1);
    ASSERT_TRUE(v2->edges().front() == e1->twin);
    
    ASSERT_EQ(v3->edges().size(), 1);
    ASSERT_TRUE(v3->edges().front() == e2->twin);
}

TEST(test_vertex, mergeEdge)
{
    Mesh m;

    HalfEdge* e1 = m.addEdge(0, 0, 0, 1);
    Vertex* v1 = e1->origin;

    HalfEdge e2(v1);
    
    Vertex v2(1, 0);
    HalfEdge e3(&v2);

    e2.twin = &e3;
    e3.twin = &e2;

    v1->mergeEdge(&e2);
    ASSERT_EQ(e1->prev, &e3);
    ASSERT_EQ(e2.prev, e1->twin);
    ASSERT_EQ(e3.next, e1);

    v2.mergeEdge(&e3); 
    ASSERT_EQ(e2.next, &e3);
    ASSERT_EQ(e3.prev, &e2);
}

