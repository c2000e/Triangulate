#include "gtest/gtest.h"

#include "Triangulate/cycle.h"

class test_cycle : public::testing::Test
{
    protected:
        std::vector<Vertex> vertices;
        std::vector<HalfEdge> edges;
        Cycle ccw_square;
        Cycle cw_square;

        void SetUp() override
        {
            // cw: e0->e1->e2->e3
            //        e3
            //   *----------*
            //   |          |
            // e2|          |e4
            //   |          |
            //   |          |
            //   *----------*
            //        e1                                                        

            // ccw: e7->e6->e5->e4
            //
            //   *----------*
            //   |    e7    |
            //   |e6      e4|
            //   |          |
            //   |    e5    |
            //   *----------*
            //                

            vertices.push_back(Vertex( 1.0,  1.0));
            vertices.push_back(Vertex( 1.0, -1.0));
            vertices.push_back(Vertex(-1.0, -1.0));
            vertices.push_back(Vertex(-1.0,  1.0));

            edges.reserve(8);
            for (int i = 1; i < 4; i++)
            {
                edges[i].origin = &vertices[i];
                edges[i].twin = &edges[i + 4];
                edges[i].next = &edges[i + 1];
                edges[i].prev = &edges[i - 1];
            }
            edges[0].origin = &vertices[0];
            edges[0].twin = &edges[4];
            edges[0].next = &edges[1];
            edges[0].prev = &edges[3];
            edges[3].next = &edges[0];

            for (int i = 4; i < 7; i++)
            {
                edges[i].origin = &vertices[i - 3];
                edges[i].twin = &edges[i - 4];
                edges[i].next = &edges[i - 1];
                edges[i].prev = &edges[i + 1];
            }
            edges[4].next = &edges[7];
            edges[7].origin = &vertices[0];
            edges[7].twin = &edges[3];
            edges[7].next = &edges[6];
            edges[7].prev = &edges[4];

            for (int i = 0; i < 4; i++)
            {
                cw_square.edges.push_back(&edges[i]);
            }

            for (int i = 4; i < 8; i++)
            {
                ccw_square.edges.push_back(&edges[i]);
            }
        }
};

TEST_F(test_cycle, lowerLeftVertex)
{
    ASSERT_EQ(*cw_square.lowerLeftVertex(), vertices[2]);
    ASSERT_EQ(*ccw_square.lowerLeftVertex(), vertices[2]);
}

TEST_F(test_cycle, lowerLeftEdge)
{
    ASSERT_EQ(*cw_square.lowerLeftEdge(), edges[2]);
    ASSERT_EQ(*ccw_square.lowerLeftEdge(), edges[5]);
}

TEST_F(test_cycle, isFace)
{
    ASSERT_FALSE(cw_square.isFace());
    ASSERT_TRUE(ccw_square.isFace());
}

