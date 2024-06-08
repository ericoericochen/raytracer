#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>
#include "utils.cpp"

using namespace std;

class Matrix
{
private:
    vector<vector<double>> m_matrix;
    int m_dim;

public:
    Matrix() {}
    Matrix(int dim, vector<vector<double>> &values)
    {
        assert(values.size() == dim && values[0].size() == dim);
        assert(dim == 2 || dim == 3 || dim == 4);

        m_matrix = values;
        m_dim = dim;
    }

    int dim() const { return m_dim; }

    bool operator==(Matrix &other) const
    {
        if (this->m_dim != other.m_dim)
            return false;

        for (int i = 0; i < this->m_dim; i++)
        {
            for (int j = 0; j < this->m_dim; j++)
            {
                bool is_equal = equal(
                    this->get(i, j), other.get(i, j));

                if (!is_equal)
                    return false;
            }
        }

        return true;
    }

    bool operator!=(Matrix &other) const { return !(*this == other); }

    double get(int i, int j) const
    {
        assert(0 <= i && i < m_dim && 0 <= j && j < m_dim);
        return this->m_matrix[i][j];
    }

    Matrix matmul(const Matrix &other) const
    {
        assert(this->m_dim == other.m_dim);

        vector<vector<double>> val = {};

        for (int i = 0; i < this->m_dim; i++)
        {
            vector<double> row = {};
            for (int j = 0; j < this->m_dim; j++)
            {
                double element = 0;
                for (int k = 0; k < this->m_dim; k++)
                {
                    element += this->get(i, k) * other.get(k, j);
                }
                row.push_back(element);
            }

            val.push_back(row);
        }

        return Matrix(this->m_dim, val);
    }

    Matrix submatrix() const
    {
    }

    string to_string() const
    {
        // get max width of a cell
        int max_length = 0;
        for (const auto &row : m_matrix)
        {
            for (const auto &value : row)
            {
                string value_str = std::to_string(value);
                int length = value_str.length();

                if (length > max_length)
                {
                    max_length = length;
                }
            }
        }

        stringstream ss;
        for (const auto &row : m_matrix)
        {
            for (int i = 0; i < row.size(); i++)
            {
                double value = row[i];
                string value_str = std::to_string(value);
                int remaining_space = max_length - value_str.length();
                string space(remaining_space, ' ');

                if (i == 0)
                {
                    ss << "|";
                }
                ss << space << value_str << "|";
            }
            ss << "\n";
        }
        return ss.str();
    }
};