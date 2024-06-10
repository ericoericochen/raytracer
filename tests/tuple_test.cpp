#include <cassert>
#include <cmath>
#include "../src/tuple.h"
#include "../src/utils.h"

int main()
{
    Tuple a, b;
    a = tuple::tuple(4.3, -4.2, 3.1, 1.0);
    assert(a.is_point() && !a.is_vector());

    b = tuple::tuple(4.3, -4.2, 3.1, 0.0);
    assert(!b.is_point() && b.is_vector());

    // equality
    a = b = tuple::point(4.3, -4.2, 3.1);
    assert(a == b);

    // addition
    a = tuple::tuple(3, -2, 5, 1);
    b = tuple::tuple(-2, 3, 1, 0);

    assert(a + b == tuple::tuple(1, 1, 6, 1));

    // subtraction
    a = tuple::point(3, 2, 1);
    b = tuple::point(5, 6, 7);

    assert(a - b == tuple::vec(-2, -4, -6)); // subtract 2 points to get a vector

    a = tuple::point(3, 2, 1);
    b = tuple::vec(5, 6, 7);

    assert(a - b == tuple::point(-2, -4, -6)); // subtract a vector from a point to get a point

    a = tuple::vec(3, 2, 1);
    b = tuple::vec(5, 6, 7);

    assert(a - b == tuple::vec(-2, -4, -6)); // subtract 2 vectors to get a vector

    // negation
    a = tuple::tuple(1, -2, 3, -4);
    assert(-a == tuple::tuple(-1, 2, -3, 4));

    // scalar multiplication
    a = tuple::tuple(1, -2, 3, -4);
    assert(a * 3.5 == tuple::tuple(3.5, -7, 10.5, -14));
    assert(a * 0.5 == tuple::tuple(0.5, -1, 1.5, -2));

    // division
    a = tuple::tuple(1, -2, 3, -4);
    assert(a / 2 == tuple::tuple(0.5, -1, 1.5, -2));

    // magnitude
    a = tuple::vec(0, 1, 0);
    assert(equal(a.magnitude(), 1));
    a = tuple::vec(0, 0, 1);
    assert(equal(a.magnitude(), 1));
    a = tuple::vec(1, 2, 3);
    assert(equal(a.magnitude(), sqrt(14)));
    a = tuple::vec(-1, -2, -3);
    assert(equal(a.magnitude(), sqrt(14)));

    // normalization
    a = tuple::vec(4, 0, 0);
    assert(a.normalize() == tuple::vec(1, 0, 0));
    a = tuple::vec(1, 2, 3);
    assert(a.normalize() == tuple::vec(0.26726, 0.53452, 0.80178));
    assert(a.normalize().magnitude() == 1);

    // dot product
    a = tuple::vec(1, 2, 3);
    b = tuple::vec(2, 3, 4);
    assert(a.dot(b) == 20);

    // cross product
    a = tuple::vec(1, 2, 3);
    b = tuple::vec(2, 3, 4);

    assert(a.cross(b) == tuple::vec(-1, 2, -1));
    assert(b.cross(a) == tuple::vec(1, -2, 1));

    return 0;
}