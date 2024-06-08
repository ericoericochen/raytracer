#include "../src/tuple.cpp"

int main()
{
    Tuple a, b;
    a = create_tuple(4.3, -4.2, 3.1, 1.0);
    assert(a.is_point() && !a.is_vector());

    b = create_tuple(4.3, -4.2, 3.1, 0.0);
    assert(!b.is_point() && b.is_vector());

    // equality
    a = b = create_point(4.3, -4.2, 3.1);
    assert(a == b);

    // addition
    a = create_tuple(3, -2, 5, 1);
    b = create_tuple(-2, 3, 1, 0);

    assert(a + b == create_tuple(1, 1, 6, 1));

    // subtraction
    a = create_point(3, 2, 1);
    b = create_point(5, 6, 7);

    assert(a - b == create_vector(-2, -4, -6)); // subtract 2 points to get a vector

    a = create_point(3, 2, 1);
    b = create_vector(5, 6, 7);

    assert(a - b == create_point(-2, -4, -6)); // subtract a vector from a point to get a point

    a = create_vector(3, 2, 1);
    b = create_vector(5, 6, 7);

    assert(a - b == create_vector(-2, -4, -6)); // subtract 2 vectors to get a vector

    // negation
    a = create_tuple(1, -2, 3, -4);
    assert(-a == create_tuple(-1, 2, -3, 4));

    // scalar multiplication
    a = create_tuple(1, -2, 3, -4);
    assert(a * 3.5 == create_tuple(3.5, -7, 10.5, -14));
    assert(a * 0.5 == create_tuple(0.5, -1, 1.5, -2));

    // division
    a = create_tuple(1, -2, 3, -4);
    assert(a / 2 == create_tuple(0.5, -1, 1.5, -2));

    // magnitude
    a = create_vector(0, 1, 0);
    assert(equal(a.magnitude(), 1));
    a = create_vector(0, 0, 1);
    assert(equal(a.magnitude(), 1));
    a = create_vector(1, 2, 3);
    assert(equal(a.magnitude(), sqrt(14)));
    a = create_vector(-1, -2, -3);
    assert(equal(a.magnitude(), sqrt(14)));

    // normalization
    a = create_vector(4, 0, 0);
    assert(a.normalize() == create_vector(1, 0, 0));
    a = create_vector(1, 2, 3);
    assert(a.normalize() == create_vector(0.26726, 0.53452, 0.80178));
    assert(a.normalize().magnitude() == 1);

    // dot product
    a = create_vector(1, 2, 3);
    b = create_vector(2, 3, 4);
    assert(a.dot(b) == 20);

    // cross product
    a = create_vector(1, 2, 3);
    b = create_vector(2, 3, 4);

    assert(a.cross(b) == create_vector(-1, 2, -1));
    assert(b.cross(a) == create_vector(1, -2, 1));

    return 0;
}