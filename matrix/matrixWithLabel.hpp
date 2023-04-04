#ifndef MATRIX_WITH_LABEL_HPP
#define MATRIX_WITH_LABEL_HPP

#include "matrix.hpp"

class MatrixWithLabel : public Matrix
{
  private:
    std::string label{"A"};

  public:
    using Matrix::Matrix;

    MatrixWithLabel(std::string label, std::size_t height, std::size_t width)
        : Matrix(height, width), label(std::move(label))
    {
    }

    MatrixWithLabel(std::string label, const std::initializer_list<std::initializer_list<double>> &list)
        : Matrix(list), label(std::move(label))
    {
    }

    const std::string &getLabel() const;

    void setLabel(const std::string &label);

    MatrixWithLabel(const MatrixWithLabel &m) : Matrix(m), label(std::move(m.label))
    {
    }

    MatrixWithLabel(MatrixWithLabel &&m) = default;

    MatrixWithLabel &operator=(MatrixWithLabel &&m) = default;
};

#endif