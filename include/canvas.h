#include <vector>
#include <string>
#include <algorithm>
#include "color.h"

#ifndef CANVAS_H
#define CANVAS_H

class Canvas
{
private:
    int m_width, m_height;
    std::vector<std::vector<Color>> m_pixels;

public:
    Canvas(int width, int height);

    std::vector<Color> operator[](int i) const;
    int width() const;
    int height() const;
    std::vector<std::vector<Color>> pixels() const;

    const Color &pixel_at(int x, int y) const;
    void write_pixel(int x, int y, Color color);

    std::string to_ppm() const;
};

#endif