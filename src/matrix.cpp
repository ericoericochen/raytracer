#include <cassert>
#include <sstream>
#include "../include/matrix.h"
#include "../include/utils.h"
#include "../include/tuple.h"

Matrix::Matrix(int dim) : m_dim(dim) { m_matrix = new double[dim * dim]; }
Matrix::Matrix(int dim, double *values)
{
    assert(dim == 2 || dim == 3 || dim == 4);

    m_matrix = new double[dim * dim];
    for (int i = 0; i < dim * dim; i++)
    {
        m_matrix[i] = values[i];
    }

    m_dim = dim;
}
Matrix::~Matrix() { delete[] m_matrix; }

int Matrix::dim() const { return m_dim; }

bool Matrix::operator==(Matrix &other) const
{
    if (this->m_dim != other.m_dim)
    {
        return false;
    }

    for (int i = 0; i < this->m_dim; i++)
    {
        for (int j = 0; j < this->m_dim; j++)
        {
            bool is_equal = equal(
                this->get(i, j), other.get(i, j));

            if (!is_equal)
            {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::operator!=(Matrix &other) const { return !(*this == other); }

double Matrix::get(int i, int j) const
{
    assert(0 <= i && i < m_dim && 0 <= j && j < m_dim);
    return m_matrix[i * m_dim + j];
}

void Matrix::set(int i, int j, double val)
{
    assert(0 <= i && i < m_dim && 0 <= j && j < m_dim);
    m_matrix[i * m_dim + j] = val;
}

Matrix Matrix::T() const
{
    Matrix matrix = Matrix(m_dim);
    for (int i = 0; i < m_dim; i++)
    {
        for (int j = 0; j < m_dim; j++)
        {
            matrix.set(i, j, this->get(j, i));
        }
    }

    return matrix;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    assert(this->m_dim == other.m_dim);

    double val[m_dim * m_dim];
    for (int i = 0; i < this->m_dim; i++)
    {
        for (int j = 0; j < this->m_dim; j++)
        {
            double element = 0;
            for (int k = 0; k < this->m_dim; k++)
            {
                element += this->get(i, k) * other.get(k, j);
            }
            val[i * m_dim + j] = element;
        }
    }

    return Matrix(this->m_dim, val);
}

Tuple Matrix::operator*(const Tuple &other) const
{
    assert(this->m_dim == 4);
    double val[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            val[i] += this->get(i, j) * other[j];
        }
    }

    return tuple::tuple(val[0], val[1], val[2], val[3]);
}

double Matrix::determinant() const
{
    if (m_dim == 2)
    {
        return this->get(0, 0) * this->get(1, 1) - this->get(0, 1) * this->get(1, 0);
    }
    else
    {
        int i = 0;
        double result = 0;
        // multiply value at (i, j) by its cofactor
        for (int j = 0; j < m_dim; j++)
        {
            result += this->get(i, j) * this->cofactor(i, j);
        }

        return result;
    }
}

bool Matrix::is_invertible() const { return this->determinant() != 0; }

Matrix Matrix::submatrix(int row, int col) const
{
    assert(m_dim == 4 || m_dim == 3);

    Matrix matrix = m_dim == 4 ? Matrix(3) : Matrix(2);
    for (int i = 0; i < m_dim; i++)
    {
        for (int j = 0; j < m_dim; j++)
        {
            if (i == row || j == col)
                continue;

            int r = i > row ? i - 1 : i;
            int c = j > col ? j - 1 : j;
            matrix.set(r, c, this->get(i, j));
        }
    }

    return matrix;
}

double Matrix::minor(int i, int j) const
{
    assert(m_dim == 3 || m_dim == 4);
    return this->submatrix(i, j).determinant();
}

double Matrix::cofactor(int i, int j) const
{
    double sign = (i + j) % 2 == 0 ? 1 : -1;
    return sign * this->minor(i, j);
}

Matrix Matrix::inverse() const
{
    // inverse = transpose cofactor matrix / det
    double det = this->determinant();
    Matrix inverse_matrix = Matrix(m_dim);
    for (int i = 0; i < m_dim; i++)
    {
        for (int j = 0; j < m_dim; j++)
        {
            // transpose cofactor / det
            inverse_matrix.set(i, j, this->cofactor(j, i) / det);
        }
    }

    return inverse_matrix;
}

std::string Matrix::to_string() const
{
    // get max width of a cell
    int max_length = 0;
    for (int i = 0; i < m_dim; i++)
    {
        for (int j = 0; j < m_dim; j++)
        {
            double value = this->get(i, j);
            std::string value_str = std::to_string(value);
            int length = value_str.length();

            if (length > max_length)
            {
                max_length = length;
            }
        }
    }

    std::stringstream ss;
    for (int i = 0; i < m_dim; i++)
    {
        for (int j = 0; j < m_dim; j++)
        {
            double value = this->get(i, j);
            std::string value_str = std::to_string(value);
            int remaining_space = max_length - value_str.length();
            std::string space(remaining_space, ' ');

            if (j == 0)
            {
                ss << "|";
            }
            ss << space << value_str << "|";
        }
        ss << "\n";
    }
    return ss.str();
}

Matrix Matrix4x4(double vals[16]) { return Matrix(4, vals); }
Matrix Matrix4x4() { return Matrix(4); }

Matrix Matrix3x3(double vals[9]) { return Matrix(3, vals); }
Matrix Matrix3x3() { return Matrix(3); }

Matrix Matrix2x2(double vals[4]) { return Matrix(2, vals); }
Matrix Matrix2x2() { return Matrix(2); }

namespace matrix
{
    Matrix eye(int dim = 4)
    {
        Matrix eye = Matrix(dim);

        // set diagonals to 1
        for (int i = 0; i < dim; i++)
        {
            eye.set(i, i, 1);
        }

        return eye;
    }

    Matrix translation(double x, double y, double z)
    {
        auto matrix = eye(4);

        // set last column to x, y, z, 1
        matrix.set(0, 3, x);
        matrix.set(1, 3, y);
        matrix.set(2, 3, z);

        return matrix;
    }

    Matrix scaling(double x, double y, double z)
    {
        auto matrix = eye(4);

        // set diagonal to x, y, z, 1
        matrix.set(0, 0, x);
        matrix.set(1, 1, y);
        matrix.set(2, 2, z);

        return matrix;
    }

    Matrix rotation_x(double radians)
    {
        auto matrix = eye(4);

        matrix.set(1, 1, cos(radians));
        matrix.set(2, 1, sin(radians));
        matrix.set(1, 2, -sin(radians));
        matrix.set(2, 2, cos(radians));

        return matrix;
    }

    Matrix rotation_y(double radians)
    {
        auto matrix = eye(4);

        matrix.set(0, 0, cos(radians));
        matrix.set(2, 0, -sin(radians));
        matrix.set(0, 2, sin(radians));
        matrix.set(2, 2, cos(radians));

        return matrix;
    }

    Matrix rotation_z(double radians)
    {

        auto matrix = eye(4);

        matrix.set(0, 0, cos(radians));
        matrix.set(1, 0, sin(radians));
        matrix.set(0, 1, -sin(radians));
        matrix.set(1, 1, cos(radians));

        return matrix;
    }

    Matrix shearing(double xy = 0, double xz = 0, double yx = 0, double yz = 0, double zx = 0, double zy = 0)
    {
        auto matrix = eye(4);

        matrix.set(0, 1, xy);
        matrix.set(0, 2, xz);
        matrix.set(1, 0, yx);
        matrix.set(1, 2, yz);
        matrix.set(2, 0, zx);
        matrix.set(2, 1, zy);

        return matrix;
    }
}
