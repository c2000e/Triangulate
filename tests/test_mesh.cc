#include "gtest/gtest.h"

#include "Triangulate/mesh.h"

TEST(test_mesh, addVertex)
{
    Mesh m;

    Vertex* v1 = m.addVertex(0, 0);
    ASSERT_EQ(v1->position, Vector(0, 0));
    
    Vertex* v2 = m.addVertex(0, 0);
    ASSERT_EQ(v1, v2);
}

TEST(test_mesh, addEdge)
{
    Mesh m;

    HalfEdge* e1 = m.addEdge(0, 0, 1, 1);
    HalfEdge* e2 = m.addEdge(1, 1, 1, 0);
    HalfEdge* e3 = m.addEdge(1, 0, 0, 0);

    ASSERT_EQ(e1->next, e2);
    ASSERT_EQ(e2->next, e3);
    ASSERT_EQ(e3->next, e1);

    ASSERT_EQ(e1->twin->next, e3->twin);
    ASSERT_EQ(e3->twin->next, e2->twin);
    ASSERT_EQ(e2->twin->next, e1->twin);
}
