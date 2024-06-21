#include <cmath>
#include <iostream>

#include "../../include/patterns/stripe.h"
#include "../../include/color.h"
#include "../../include/tuple.h"

Stripe::Stripe(Color a, Color b) : a(a), b(b) {}

Color Stripe::pattern_at(const Tuple &point) const
{
    return (int)floor(point.x) % 2 == 0 ? this->a : this->b;
}