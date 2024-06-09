#include <cassert>
#include <iostream>
#include "../src/matrix.cpp"

int main()
{
    // translation
    auto transform = matrix::translation(5, -3, 2);
    auto p = primitive::point(-3, 4, 5);
    assert(transform * p == primitive::point(2, 1, 7));

    auto inv = transform.inverse();
    assert(inv * p == primitive::point(-8, 7, 3));

    // translation does not affect vectors
    auto vec = primitive::vec(-3, 4, 5);
    assert(transform * vec == vec);

    // scaling
    transform = matrix::scaling(2, 3, 4);
    p = primitive::point(-4, 6, 8);
    assert(transform * p == primitive::point(-8, 18, 32));

    transform = matrix::scaling(2, 3, 4);
    vec = primitive::vec(-4, 6, 8);
    assert(transform * vec == primitive::vec(-8, 18, 32));

    transform = matrix::scaling(2, 3, 4);
    assert(transform.inverse() * vec == primitive::vec(-2, 2, 2));

    // reflection
    transform = matrix::scaling(-1, 1, 1);
    p = primitive::point(2, 3, 4);
    assert(transform * p == primitive::point(-2, 3, 4));

    // rotation about x axis
    p = primitive::point(0, 1, 0);
    auto half_quarter = matrix::rotation_x(M_PI / 4);
    auto full_quarter = matrix::rotation_x(M_PI / 2);

    assert(half_quarter * p == primitive::point(0, sqrt(2) / 2, sqrt(2) / 2));
    assert(full_quarter * p == primitive::point(0, 0, 1));
    assert(half_quarter.inverse() * p == primitive::point(0, sqrt(2) / 2, -sqrt(2) / 2));

    // rotation about y axis
    p = primitive::point(0, 0, 1);
    half_quarter = matrix::rotation_y(M_PI / 4);
    full_quarter = matrix::rotation_y(M_PI / 2);

    assert(half_quarter * p == primitive::point(sqrt(2) / 2, 0, sqrt(2) / 2));
    assert(full_quarter * p == primitive::point(1, 0, 0));

    // rotation about z axis
    p = primitive::point(0, 1, 0);
    half_quarter = matrix::rotation_z(M_PI / 4);
    full_quarter = matrix::rotation_z(M_PI / 2);

    assert(half_quarter * p == primitive::point(-sqrt(2) / 2, sqrt(2) / 2, 0));
    assert(full_quarter * p == primitive::point(-1, 0, 0));

    // shearing
    p = primitive::point(2, 3, 4);
    transform = matrix::shearing(1, 0, 0, 0, 0, 0);
    assert(transform * p == primitive::point(5, 3, 4));

    // TOOD: implement rest of test cases

    return 0;
}