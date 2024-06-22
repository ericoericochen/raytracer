#ifndef PATTERN_H
#define PATTERN_H

#include "../matrix.h"
#include "../tuple.h"
#include "../color.h"
#include "../transforms.h"

class Pattern
{
public:
    Matrix transform = transforms::eye();

    Pattern();
    ~Pattern();
    virtual Color pattern_at(const Tuple &point) const;
};

#endif