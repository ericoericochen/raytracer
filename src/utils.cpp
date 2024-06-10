#include <cmath>
#include "../include/utils.h"

bool equal(double a, double b)
{
    return std::abs(a - b) < EPSILON;
}
