#ifndef RING_H
#define RING_H

#include "../matrix.h"
#include "../color.h"
#include "../tuple.h"
#include "../transforms.h"
#include "./pattern.h"

class Ring : public Pattern
{
public:
    Color a, b;
    Ring(Color a, Color b);
    Color pattern_at(const Tuple &point) const override;
};

#endif