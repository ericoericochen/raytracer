#include <cassert>
#include <iostream>
#include "../include/matrix.h"
#include "../include/tuple.h"

// write test functions ie. test_translation1, test_translation2, test_scaling.
// START

void test_translation1()
{
    auto transform = matrix::translation(5, -3, 2);
    auto p = tuple::point(-3, 4, 5);
    assert(transform * p == tuple::point(2, 1, 7));
}

void test_translation2()
{
    auto transform = matrix::translation(5, -3, 2);
    auto p = tuple::point(-3, 4, 5);
    auto inv = transform.inverse();
    assert(inv * p == tuple::point(-8, 7, 3));
}

void test_scaling1()
{
    auto transform = matrix::scaling(2, 3, 4);
    auto p = tuple::point(-4, 6, 8);
    assert(transform * p == tuple::point(-8, 18, 32));
}

// write the rest ...

// END

int main()
{
    // translation
    auto transform = matrix::translation(5, -3, 2);
    auto p = tuple::point(-3, 4, 5);
    assert(transform * p == tuple::point(2, 1, 7));

    auto inv = transform.inverse();
    assert(inv * p == tuple::point(-8, 7, 3));

    // translation does not affect vectors
    auto vec = tuple::vec(-3, 4, 5);
    assert(transform * vec == vec);

    // scaling
    transform = matrix::scaling(2, 3, 4);
    p = tuple::point(-4, 6, 8);

    std::cout << (transform * p).to_string() << std::endl;
    assert(transform * p == tuple::point(-8, 18, 32));

    transform = matrix::scaling(2, 3, 4);
    vec = tuple::vec(-4, 6, 8);
    assert(transform * vec == tuple::vec(-8, 18, 32));

    transform = matrix::scaling(2, 3, 4);
    assert(transform.inverse() * vec == tuple::vec(-2, 2, 2));

    // reflection
    transform = matrix::scaling(-1, 1, 1);
    p = tuple::point(2, 3, 4);
    assert(transform * p == tuple::point(-2, 3, 4));

    // rotation about x axis
    p = tuple::point(0, 1, 0);
    auto half_quarter = matrix::rotation_x(M_PI / 4);
    auto full_quarter = matrix::rotation_x(M_PI / 2);

    assert(half_quarter * p == tuple::point(0, sqrt(2) / 2, sqrt(2) / 2));
    assert(full_quarter * p == tuple::point(0, 0, 1));
    assert(half_quarter.inverse() * p == tuple::point(0, sqrt(2) / 2, -sqrt(2) / 2));

    // rotation about y axis
    p = tuple::point(0, 0, 1);
    half_quarter = matrix::rotation_y(M_PI / 4);
    full_quarter = matrix::rotation_y(M_PI / 2);

    assert(half_quarter * p == tuple::point(sqrt(2) / 2, 0, sqrt(2) / 2));
    assert(full_quarter * p == tuple::point(1, 0, 0));

    // rotation about z axis
    p = tuple::point(0, 1, 0);
    half_quarter = matrix::rotation_z(M_PI / 4);
    full_quarter = matrix::rotation_z(M_PI / 2);

    assert(half_quarter * p == tuple::point(-sqrt(2) / 2, sqrt(2) / 2, 0));
    assert(full_quarter * p == tuple::point(-1, 0, 0));

    // shearing
    p = tuple::point(2, 3, 4);
    transform = matrix::shearing(1, 0, 0, 0, 0, 0);
    assert(transform * p == tuple::point(5, 3, 4));

    // TOOD: implement rest of test cases

    return 0;
}