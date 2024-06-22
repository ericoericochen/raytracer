#include <cassert>
#include <iostream>
#include "../include/color.h"
#include "../include/patterns/stripe.h"
#include "../include/patterns/pattern.h"
#include "../include/patterns/gradient.h"
#include "../include/patterns/ring.h"
#include "../include/tuple.h"
#include "../include/shapes/sphere.h"
#include "../include/transforms.h"

int main()
{
    auto black = Color(0, 0, 0);
    auto white = Color(1, 1, 1);

    Stripe pattern = Stripe(white, black);

    assert(pattern.a == white && pattern.b == black);

    assert(pattern.pattern_at(tuple::point(0, 0, 0)) == white);
    assert(pattern.pattern_at(tuple::point(0, 1, 0)) == white);
    assert(pattern.pattern_at(tuple::point(0, 2, 0)) == white);

    assert(pattern.pattern_at(tuple::point(0, 0, 0)) == white);
    assert(pattern.pattern_at(tuple::point(0, 0, 1)) == white);
    assert(pattern.pattern_at(tuple::point(0, 0, 2)) == white);

    assert(pattern.pattern_at(tuple::point(0, 0, 0)) == white);
    assert(pattern.pattern_at(tuple::point(0.9, 0, 0)) == white);
    assert(pattern.pattern_at(tuple::point(1, 0, 0)) == black);
    assert(pattern.pattern_at(tuple::point(-0.1, 0, 0)) == black);
    assert(pattern.pattern_at(tuple::point(-1, 0, 0)) == black);
    assert(pattern.pattern_at(tuple::point(-1.1, 0, 0)) == white);

    // Stripes with an object transformation
    auto object = Sphere();
    object.transform = transforms::scaling(2, 2, 2);
    object.material.pattern = new Stripe(white, black);
    assert(object.pattern_at(tuple::point(1.5, 0, 0)) == white);

    // Stripes with a pattern transformation
    object = Sphere();
    object.material.pattern = new Stripe(white, black);
    object.material.pattern->transform = transforms::scaling(2, 2, 2);
    assert(object.pattern_at(tuple::point(1.5, 0, 0)) == white);

    // Stripes with both an object and a pattern transformation
    object = Sphere();
    object.transform = transforms::scaling(2, 2, 2);
    object.material.pattern = new Stripe(white, black);
    object.material.pattern->transform = transforms::translation(.5, 0, 0);
    assert(object.pattern_at(tuple::point(2.5, 0, 0)) == white);

    // patterns
    auto test_pattern = Pattern();
    assert(pattern.transform == transforms::eye());

    pattern.transform = transforms::translation(1, 2, 3);
    assert(pattern.transform == transforms::translation(1, 2, 3));

    //  A pattern with an object transformation
    auto shape = Sphere();
    shape.transform = transforms::scaling(2, 2, 2);
    shape.material.pattern = new Pattern();
    auto c = shape.pattern_at(tuple::point(2, 3, 4));

    std::cout << c.to_string() << std::endl;

    assert(c == Color(1, 1.5, 2));

    // A pattern with a pattern transformation
    shape = Sphere();
    shape.material.pattern = new Pattern();
    shape.material.pattern->transform = transforms::scaling(2, 2, 2);
    c = shape.pattern_at(tuple::point(2, 3, 4));
    assert(c == Color(1, 1.5, 2));

    // A pattern with both an object and a pattern transformation
    shape = Sphere();
    shape.transform = transforms::scaling(2, 2, 2);
    shape.material.pattern = new Pattern();
    shape.material.pattern->transform = transforms::translation(.5, 1, 1.5);
    c = shape.pattern_at(tuple::point(2.5, 3, 3.5));
    assert(c == Color(0.75, 0.5, 0.25));

    // A gradient linearly interpolates between colors
    auto gradient = Gradient(white, black);
    assert(gradient.pattern_at(tuple::point(0, 0, 0)) == white);
    assert(gradient.pattern_at(tuple::point(0.25, 0, 0)) == Color(0.75, 0.75, 0.75));
    assert(gradient.pattern_at(tuple::point(0.5, 0, 0)) == Color(0.5, 0.5, 0.5));
    assert(gradient.pattern_at(tuple::point(0.75, 0, 0)) == Color(0.25, 0.25, 0.25));

    // A ring should extend in both x and z
    auto ring = Ring(white, black);
    assert(ring.pattern_at(tuple::point(0, 0, 0)) == white);
    assert(ring.pattern_at(tuple::point(1, 0, 0)) == black);
    assert(ring.pattern_at(tuple::point(0, 0, 1)) == black);
    assert(ring.pattern_at(tuple::point(0.708, 0, 0.708)) == black);
}