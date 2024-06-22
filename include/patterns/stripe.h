#ifndef STRIPE_H
#define STRIPE_H

#include "../matrix.h"
#include "../color.h"
#include "../tuple.h"
#include "../transforms.h"
#include "./pattern.h"

class Stripe : public Pattern
{
public:
    Color a, b;
    // Matrix transform = transforms::eye();

    Stripe(Color a, Color b);

    Color pattern_at(const Tuple &point) const override;
};

#endif