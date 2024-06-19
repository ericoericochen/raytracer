#include <cassert>
#include <iostream>
#include "../include/utils.h"
#include "../include/camera.h"
#include "../include/tuple.h"
#include "../include/matrix.h"
#include "../include/world.h"
#include "../include/color.h"

int main()
{
    Camera c = Camera(
        200,
        125,
        M_PI / 2);

    assert(equal(c.pixel_size(), 0.01));

    c = Camera(
        125,
        200,
        M_PI / 2);

    assert(equal(c.pixel_size(), 0.01));

    c = Camera(201, 101, M_PI / 2);
    auto r = c.ray_for_pxiel(100, 50);

    assert(r.origin == tuple::point(0, 0, 0) && r.direction == tuple::vec(0, 0, -1));

    c = Camera(201, 101, M_PI / 2);
    r = c.ray_for_pxiel(0, 0);

    assert(r.origin == tuple::point(0, 0, 0) && r.direction == tuple::vec(0.66519, 0.33259, -0.66851));

    c = Camera(201, 101, M_PI / 2);
    c.transform = matrix::rotation_y(M_PI / 4) * matrix::translation(0, -2, 5);
    r = c.ray_for_pxiel(100, 50);

    assert(r.origin == tuple::point(0, 2, -5) && r.direction == tuple::vec(sqrt(2) / 2, 0, -sqrt(2) / 2));

    World w = World();
    c = Camera(11, 11, M_PI / 2);
    auto from = tuple::point(0, 0, -5);
    auto to = tuple::point(0, 0, 0);
    auto up = tuple::vec(0, 1, 0);
    c.transform = matrix::view_transform(from, to, up);
    auto image = w.render(c);

    std::cout << image.pixel_at(5, 5).to_string() << std::endl;

    // assert(image.pixel_at(5, 5) == Color(0.38066, 0.47583, 0.2855));
}