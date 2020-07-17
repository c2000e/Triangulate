#include "gtest/gtest.h"

#include "Triangulate/vector.h"

#include <cmath>

TEST(test_vector, inverse)
{
    ASSERT_EQ(-Vector(1, 1), Vector(-1, -1));
}

TEST(test_vector, add)
{
    // identity
    Vector a(1, 1);
    ASSERT_EQ(a + Vector(0, 0), a);

    // commutative
    Vector b(2, 2);
    ASSERT_EQ(a + b, b + a);

    // associative
    Vector c(3, 3);
    ASSERT_EQ((a + b) + c, a + (b + c));

    // additive inverse
    ASSERT_EQ(a + -a, Vector(0, 0));
}

TEST(test_vector, subtract)
{
    // identity
    Vector a(1, 1);
    ASSERT_EQ(a - Vector(0, 0), a);

    // not commutative
    Vector b(2, 2);
    ASSERT_NE(a - b, b - a);

    // not associative
    Vector c(3, 3);
    ASSERT_NE((a - b) - c, a - (b - c));

    // additive inverse 
    ASSERT_EQ(a - a, Vector(0, 0));
}

TEST(test_vector, multiply)
{
    Vector a(1, 1);

    // identity
    int c = 1;
    ASSERT_EQ(a * c, a);

    // zero
    c = 0;
    ASSERT_EQ(a * c, Vector(0, 0));

    // flip
    c = -1;
    ASSERT_EQ(a * c, Vector(-1, -1));

    // scale
    c = 5;
    ASSERT_EQ(a * c, Vector(5, 5));
}

TEST(test_vector, divide)
{
    Vector a(1, 1);

    // identity
    int c = 1;
    ASSERT_EQ(a / c, a);

    // flip
    c = -1;
    ASSERT_EQ(a / c, Vector(-1, -1));
}

TEST(test_vector, sqrMagnitude)
{
    // +x axis
    Vector a(2, 0);
    ASSERT_EQ(a.sqrMagnitude(), 4);

    // quadrant 1
    a = Vector(2, 2);
    ASSERT_EQ(a.sqrMagnitude(), 8);
    
    // +y axis
    a = Vector(0, 2);
    ASSERT_EQ(a.sqrMagnitude(), 4);

    // quadrant 2
    a = Vector(-2, 2);
    ASSERT_EQ(a.sqrMagnitude(), 8);

    // -x axis
    a = Vector(-2, 0);
    ASSERT_EQ(a.sqrMagnitude(), 4);

    // quadrant 3
    a = Vector(-2, -2);
    ASSERT_EQ(a.sqrMagnitude(), 8);

    // -y axis
    a = Vector(0, -2);
    ASSERT_EQ(a.sqrMagnitude(), 4);

    // quadrant 4
    a = Vector(2, -2);
    ASSERT_EQ(a.sqrMagnitude(), 8);
}

TEST(test_vector, dot)
{
    Vector a(1, 1);

    // zero
    ASSERT_EQ(dot(a, Vector(0, 0)), 0);

    // positive
    ASSERT_EQ(dot(a, a), 2);

    // negative
    ASSERT_EQ(dot(a, -a), -2);
}

TEST(test_vector, det)
{
    Vector a(1, 1);

    // zero
    ASSERT_EQ(det(a, Vector(0, 0)), 0);

    Vector b(-1, 1);
    ASSERT_EQ(det(a, b), 2);
    ASSERT_EQ(det(b, a), -2);
}

TEST(test_vector, cwLess)
{
    Vector center(4, -16);

    std::vector<Vector> vectors;
    vectors.push_back(Vector( 0,  1) + center);
    vectors.push_back(Vector( 1,  1) + center);
    vectors.push_back(Vector( 1,  0) + center);
    vectors.push_back(Vector( 1, -1) + center);
    vectors.push_back(Vector( 0, -1) + center);
    vectors.push_back(Vector(-1, -1) + center);
    vectors.push_back(Vector(-1,  0) + center);
    vectors.push_back(Vector(-1,  1) + center);

    for (int i = 0; i < vectors.size() - 1; i++)
    {
        for (int j = i + 1; j < vectors.size(); j++)
        {
            ASSERT_TRUE(cwLess(vectors[i], vectors[j], center));
            ASSERT_FALSE(cwLess(vectors[j], vectors[i], center));
        }
    }
}

