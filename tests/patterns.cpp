#include <cassert>
#include "../include/color.h"
#include "../include/patterns/stripe.h"
#include "../include/tuple.h"

int main()
{
    auto black = Color(0, 0, 0);
    auto white = Color(1, 1, 1);

    auto pattern = Stripe(white, black);

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

}