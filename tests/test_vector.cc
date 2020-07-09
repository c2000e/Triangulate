#include "gtest/gtest.h"

#include "Triangulate/vector.h"

#include <cmath>

TEST(test_vector, inverse)
{
    ASSERT_EQ(-Vector(1.0, 1.0), Vector(-1.0, -1.0));
}

TEST(test_vector, add)
{
    // identity
    Vector a(1.0, 1.0);
    ASSERT_EQ(a + Vector(0.0, 0.0), a);

    // commutative
    Vector b(2.0, 2.0);
    ASSERT_EQ(a + b, b + a);

    // associative
    Vector c(3.0, 3.0);
    ASSERT_EQ((a + b) + c, a + (b + c));

    // additive inverse
    ASSERT_EQ(a + -a, Vector(0.0, 0.0));
}

TEST(test_vector, subtract)
{
    // identity
    Vector a(1.0, 1.0);
    ASSERT_EQ(a - Vector(0.0, 0.0), a);

    // not commutative
    Vector b(2.0, 2.0);
    ASSERT_NE(a - b, b - a);

    // not associative
    Vector c(3.0, 3.0);
    ASSERT_NE((a - b) - c, a - (b - c));

    // additive inverse 
    ASSERT_EQ(a - a, Vector(0.0, 0.0));
}

TEST(test_vector, multiply)
{
    Vector a(1.0, 1.0);

    // identity
    double c = 1.0;
    ASSERT_EQ(a * c, a);

    // zero
    c = 0.0;
    ASSERT_EQ(a * c, Vector(0.0, 0.0));

    // flip
    c = -1.0;
    ASSERT_EQ(a * c, Vector(-1.0, -1.0));

    // scale
    c = 5.0;
    ASSERT_EQ(a * c, Vector(5.0, 5.0));
}

TEST(test_vector, divide)
{
    Vector a(1.0, 1.0);

    // identity
    double c = 1.0;
    ASSERT_EQ(a / c, a);

    // flip
    c = -1.0;
    ASSERT_EQ(a / c, Vector(-1.0, -1.0));

    // scale
    c = 5.0;
    ASSERT_EQ(a / c, Vector(0.2, 0.2));
}

TEST(test_vector, sqrMagnitude)
{
    // +x axis
    Vector a(2.0, 0.0);
    ASSERT_DOUBLE_EQ(a.sqrMagnitude(), 4.0);

    // quadrant 1
    a = Vector(2.0, 2.0);
    ASSERT_DOUBLE_EQ(a.sqrMagnitude(), 8.0);
    
    // +y axis
    a = Vector(0.0, 2.0);
    ASSERT_DOUBLE_EQ(a.sqrMagnitude(), 4.0);

    // quadrant 2
    a = Vector(-2.0, 2.0);
    ASSERT_DOUBLE_EQ(a.sqrMagnitude(), 8.0);

    // -x axis
    a = Vector(-2.0, 0.0);
    ASSERT_DOUBLE_EQ(a.sqrMagnitude(), 4.0);

    // quadrant 3
    a = Vector(-2.0, -2.0);
    ASSERT_DOUBLE_EQ(a.sqrMagnitude(), 8.0);

    // -y axis
    a = Vector(0.0, -2.0);
    ASSERT_DOUBLE_EQ(a.sqrMagnitude(), 4.0);

    // quadrant 4
    a = Vector(2.0, -2.0);
    ASSERT_DOUBLE_EQ(a.sqrMagnitude(), 8.0);
}

TEST(test_vector, magnitude)
{
    // +x axis
    Vector a(2.0, 0.0);
    ASSERT_DOUBLE_EQ(a.magnitude(), 2.0);

    // quadrant 1
    a = Vector(2.0, 2.0);
    ASSERT_DOUBLE_EQ(a.magnitude(), std::sqrt(8.0));
    
    // +y axis
    a = Vector(0.0, 2.0);
    ASSERT_DOUBLE_EQ(a.magnitude(), 2.0);

    // quadrant 2
    a = Vector(-2.0, 2.0);
    ASSERT_DOUBLE_EQ(a.magnitude(), std::sqrt(8.0));

    // -x axis
    a = Vector(-2.0, 0.0);
    ASSERT_DOUBLE_EQ(a.magnitude(), 2.0);

    // quadrant 3
    a = Vector(-2.0, -2.0);
    ASSERT_DOUBLE_EQ(a.magnitude(), std::sqrt(8.0));

    // -y axis
    a = Vector(0.0, -2.0);
    ASSERT_DOUBLE_EQ(a.magnitude(), 2.0);

    // quadrant 4
    a = Vector(2.0, -2.0);
    ASSERT_DOUBLE_EQ(a.magnitude(), std::sqrt(8.0));
}

TEST(test_vector, direction)
{
    // +x axis
    Vector a(1.0, 0.0);
    ASSERT_DOUBLE_EQ(a.direction(), 0.0);

    // quadrant 1
    a = Vector(1.0, 1.0);
    ASSERT_DOUBLE_EQ(a.direction(), PI * 0.25);

    // + y axis
    a = Vector(0.0, 1.0);
    ASSERT_DOUBLE_EQ(a.direction(), PI * 0.5);

    // quadrant 2
    a = Vector(-1.0, 1.0);
    ASSERT_DOUBLE_EQ(a.direction(), PI * 0.75);

    // -x axis
    a = Vector(-1.0, 0.0);
    ASSERT_DOUBLE_EQ(a.direction(), PI);

    // quadrant 3
    a = Vector(-1.0, -1.0);
    ASSERT_DOUBLE_EQ(a.direction(), PI * 1.25);

    // -y axis
    a = Vector(0.0, -1.0);
    ASSERT_DOUBLE_EQ(a.direction(), PI * 1.5); 

    // quadrant 4
    a = Vector(1.0, -1.0);
    ASSERT_DOUBLE_EQ(a.direction(), PI * 1.75);
}

TEST(test_vector, unit)
{
    // +x axis
    Vector a(10.0, 0.0);
    ASSERT_DOUBLE_EQ(a.unit().sqrMagnitude(), 1.0);
    ASSERT_DOUBLE_EQ(a.direction(), a.unit().direction());

    // quadrant 1
    a = Vector(10.0, 10.0);
    ASSERT_DOUBLE_EQ(a.unit().sqrMagnitude(), 1.0);
    ASSERT_DOUBLE_EQ(a.direction(), a.unit().direction());

    // + y axis
    a = Vector(0.0, 10.0);
    ASSERT_DOUBLE_EQ(a.unit().sqrMagnitude(), 1.0);
    ASSERT_DOUBLE_EQ(a.direction(), a.unit().direction());

    // quadrant 2
    a = Vector(-10.0, 10.0);
    ASSERT_DOUBLE_EQ(a.unit().sqrMagnitude(), 1.0);
    ASSERT_DOUBLE_EQ(a.direction(), a.unit().direction());

    // -x axis
    a = Vector(-10.0, 0.0);
    ASSERT_DOUBLE_EQ(a.unit().sqrMagnitude(), 1.0);
    ASSERT_DOUBLE_EQ(a.direction(), a.unit().direction());

    // quadrant 3
    a = Vector(-10.0, -10.0);
    ASSERT_DOUBLE_EQ(a.unit().sqrMagnitude(), 1.0);
    ASSERT_DOUBLE_EQ(a.direction(), a.unit().direction());

    // -y axis
    a = Vector(0.0, -10.0);
    ASSERT_DOUBLE_EQ(a.unit().sqrMagnitude(), 1.0);
    ASSERT_DOUBLE_EQ(a.direction(), a.unit().direction());

    // quadrant 4
    a = Vector(10.0, -10.0);
    ASSERT_DOUBLE_EQ(a.unit().sqrMagnitude(), 1.0);
    ASSERT_DOUBLE_EQ(a.direction(), a.unit().direction());
}

TEST(test_vector, dot)
{
    Vector a(1.0, 1.0);

    // zero
    ASSERT_DOUBLE_EQ(dot(a, Vector(0.0, 0.0)), 0.0);

    // positive
    ASSERT_DOUBLE_EQ(dot(a, a), 2.0);

    // negative
    ASSERT_DOUBLE_EQ(dot(a, -a), -2.0);
}

TEST(test_vector, det)
{
    Vector a(1.0, 1.0);

    // zero
    ASSERT_DOUBLE_EQ(det(a, Vector(0.0, 0.0)), 0.0);

    Vector b(-1.0, 1.0);
    ASSERT_DOUBLE_EQ(det(a, b), 2.0);
    ASSERT_DOUBLE_EQ(det(b, a), -2.0);
}

TEST(test_vector, angleBetween)
{
    Vector a( 1.0,  0.0);
    Vector b( 0.0,  1.0);
    Vector c(-1.0,  0.0);
    Vector d( 0.0, -1.0);
    ASSERT_DOUBLE_EQ(angleBetween(a, b), PI * 0.5);
    ASSERT_DOUBLE_EQ(angleBetween(b, a), PI * 1.5);
    ASSERT_DOUBLE_EQ(angleBetween(a, c), PI);
    ASSERT_DOUBLE_EQ(angleBetween(c, a), PI);
    ASSERT_DOUBLE_EQ(angleBetween(a, d), PI * 1.5);
    ASSERT_DOUBLE_EQ(angleBetween(d, a), PI * 0.5);
}

TEST(test_vector, cwLess)
{
    Vector center(4.0, -16.0);

    std::vector<Vector> vectors;
    vectors.push_back(Vector( 0.0,  1.0) + center);
    vectors.push_back(Vector( 1.0,  1.0) + center);
    vectors.push_back(Vector( 1.0,  0.0) + center);
    vectors.push_back(Vector( 1.0, -1.0) + center);
    vectors.push_back(Vector( 0.0, -1.0) + center);
    vectors.push_back(Vector(-1.0, -1.0) + center);
    vectors.push_back(Vector(-1.0,  0.0) + center);
    vectors.push_back(Vector(-1.0,  1.0) + center);

    for (int i = 0; i < vectors.size() - 1; i++)
    {
        for (int j = i + 1; j < vectors.size(); j++)
        {
            ASSERT_TRUE(cwLess(vectors[i], vectors[j], center));
            ASSERT_FALSE(cwLess(vectors[j], vectors[i], center));
        }
    }
}
