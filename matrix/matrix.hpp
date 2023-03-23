#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <iostream>
#include <memory>

class Matrix {
private:
  std::size_t height{0};
  std::size_t width{0};
  std::unique_ptr<double[]> data{nullptr};

public:
  Matrix() = default;

  Matrix(std::size_t height, std::size_t width) 
  : height(height), width(width), data(new double[height * width]{0.0}) 
  {
    std::cout << "Constructor of " << this->height << "x"
              << this->width << "matrix" << std::endl;
  }

  Matrix(const std::initializer_list<std::initializer_list<double>> list);

  Matrix(const Matrix& m);
  Matrix& operator=(const Matrix& m);

  Matrix(Matrix&& m);
  Matrix& operator=(Matrix&& m);

  Matrix operator-() const;

  double operator()(std::size_t row, std::size_t column) const;
  double& operator()(std::size_t row, std::size_t column);

  friend std::ostream& operator<<(std::ostream& os, const Matrix& obj);

  virtual ~Matrix();
};

#endif