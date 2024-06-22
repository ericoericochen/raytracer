#include "pattern.h"
#include "../color.h"

class Checker : public Pattern
{
public:
    Color a, b;
    Checker(Color a, Color b);
    Color pattern_at(const Tuple &point) const override;
};