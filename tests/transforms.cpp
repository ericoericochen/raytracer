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

    // view transform
    auto from = tuple::point(0, 0, 0);
    auto to = tuple::point(0, 0, -1);
    auto up = tuple::vec(0, 1, 0);
    Matrix t = matrix::view_transform(from, to, up);

    assert(t == matrix::eye(4));

    from = tuple::point(0, 0, 0);
    to = tuple::point(0, 0, 1);
    up = tuple::vec(0, 1, 0);
    t = matrix::view_transform(from, to, up);

    assert(t == matrix::scaling(-1, 1, -1));

    from = tuple::point(0, 0, 8);
    to = tuple::point(0, 0, 0);
    up = tuple::vec(0, 1, 0);
    t = matrix::view_transform(from, to, up);

    assert(t == matrix::translation(0, 0, -8));

    from = tuple::point(1, 3, 2);
    to = tuple::point(4, -2, 8);
    up = tuple::vec(1, 1, 0);
    t = matrix::view_transform(from, to, up);

    auto m = Matrix4x4(new double[16]{
        -0.50709, 0.50709, 0.67612, -2.36643, 0.76772, 0.60609, 0.12122, -2.82843,
        -0.35857, 0.59761, -0.71714, 0.00000, 0.00000, 0.00000, 0.00000, 1.00000});

    assert(t == m);

    return 0;
}