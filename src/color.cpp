#include <string>
#include "../include/tuple.h"
#include "../include/color.h"

Color::Color() : Tuple() {}
Color::Color(double r, double g, double b) : Tuple(r, g, b, 0) {}

const double &Color::r() const { return this->x; }
const double &Color::g() const { return this->y; }
const double &Color::b() const { return this->z; }

std::string Color::to_string() const
{
    return "Color(" + std::to_string(this->r()) + ", " + std::to_string(this->g()) + ", " + std::to_string(this->b()) + ")";
}