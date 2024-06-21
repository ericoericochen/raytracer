#ifndef STRIPE_H
#define STRIPE_H

#include "../matrix.h"
#include "../color.h"
#include "../tuple.h"

class Stripe
{
    // public:
    //     Matrix transform;

public:
    Color a, b;

    Stripe(Color a, Color b);

    Color pattern_at(const Tuple &point) const;
};

#endif