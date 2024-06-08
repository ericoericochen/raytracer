#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Matrix
{
private:
    vector<vector<double>> m_matrix;
    int m_dim;

public:
    Matrix(int dim, vector<vector<double>> &values)
    {
        assert(values.size() == dim && values[0].size() == dim);
        assert(dim == 2 || dim == 3 || dim == 4);

        m_matrix = values;
        m_dim = dim;
    }

    int dim() const { return m_dim; }

    double get(int i, int j) const
    {
        assert(0 <= i && i < m_dim && 0 <= j && j < m_dim);
        return this->m_matrix[i][j];
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