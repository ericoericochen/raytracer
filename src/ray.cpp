#include "tuple.cpp"
#include <cassert>

class Ray
{
public:
    Tuple origin;
    Tuple direction;

    Ray(Tuple origin, Tuple direction)
    {
        assert(origin.is_point() && direction.is_vector());
        this->origin = origin;
        this->direction = direction;
    }

    Tuple position_at(double t) const
    {
        return this->origin + this->direction * t;
    }
};