#include <vector>
#include <string>
#include <algorithm>
#include "../include/canvas.h"
#include "../include/color.h"

Canvas::Canvas(int width, int height)
{
    m_width = width;
    m_height = height;

    m_pixels = {};

    for (int j = 0; j < height; j++)
    {
        std::vector<Color> row = {};
        for (int i = 0; i < width; i++)
        {
            Color color = Color(0, 0, 0);
            row.push_back(color);
        }
        m_pixels.push_back(row);
    }
}

std::vector<Color> Canvas::operator[](int i) const { return this->m_pixels[i]; }
int Canvas::width() const { return m_width; }
int Canvas::height() const { return m_height; }
std::vector<std::vector<Color>> Canvas::pixels() const { return m_pixels; }

const Color &Canvas::pixel_at(int x, int y) const
{
    return this->m_pixels[y][x];
}

void Canvas::write_pixel(int x, int y, Color color)
{
    this->m_pixels[y][x] = color;
}

std::string Canvas::to_ppm() const
{
    std::string ppm = "P3\n" + std::to_string(m_width) + " " + std::to_string(m_height) + "\n255\n";

    for (const std::vector<Color> &row : m_pixels)
    {
        for (const Color &color : row)
        {
            int r = (int)std::clamp(color.r(), 0.0, 255.0);
            int g = (int)std::clamp(color.g(), 0.0, 255.0);
            int b = (int)std::clamp(color.b(), 0.0, 255.0);

            ppm += std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b) + "\n";
        }
    }

    return ppm;
}
