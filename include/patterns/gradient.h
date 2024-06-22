#include "pattern.h"
#include "../color.h"

class Gradient : public Pattern
{
public:
    Color a, b;
    Gradient(Color a, Color b);
    Color pattern_at(const Tuple &point) const override;
};