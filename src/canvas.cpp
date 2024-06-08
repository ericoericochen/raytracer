#include <vector>
#include "color.cpp"

using namespace std;

class Canvas
{
private:
    int m_width, m_height;
    vector<vector<Color>> m_pixels;

public:
    Canvas(int width, int height)
    {
        m_width = width;
        m_height = height;

        m_pixels = {};

        for (int j = 0; j < height; j++)
        {
            vector<Color> row = {};
            for (int i = 0; i < width; i++)
            {
                Color color = Color(0, 0, 0);
                row.push_back(color);
            }
            m_pixels.push_back(row);
        }
    }

    vector<Color> operator[](int i) const { return this->m_pixels[i]; }
    int width() const { return m_width; }
    int height() const { return m_height; }
    vector<vector<Color>> pixels() const { return m_pixels; }

    const Color &pixel_at(int x, int y) const
    {
        return this->m_pixels[y][x];
    }

    void write_pixel(int x, int y, Color color)
    {
        this->m_pixels[y][x] = color;
    }
};