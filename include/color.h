#ifndef COLOR_H
#define COLOR_H

#include <string>
#include "tuple.h"

class Color : public Tuple
{

public:
    Color();
    Color(double r, double g, double b);

    const double &r() const;
    const double &b() const;
    const double &g() const;

    std::string to_string() const;
};

#endif