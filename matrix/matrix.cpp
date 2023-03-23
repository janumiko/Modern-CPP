#include <iostream>
#include <memory>

#include "matrix.hpp"

Matrix::Matrix(const std::initializer_list<std::initializer_list<double>> list) 
{
  std::size_t height = list.size();
  std::size_t width = 0;
  for (const auto &l : list) 
  {
    width = std::max(width, l.size());
  }

  this->height = height;
  this->width = width;

  this->data = std::unique_ptr<double[]>(new double[height * width]{0.0});

  auto ptr = this->data.get();
  for (const auto& row : list) 
  {
    std::copy(row.begin(), row.end(), ptr);
    ptr += width;
  }

  std::cout << "Constructor of " << this->height << "x" << this->width
            << "matrix from initializer list" << std::endl;
}

Matrix::Matrix(const Matrix& m) : height(m.height), width(m.width), data(new double[height * width]{0.0})
{ 
  std::cout << "Copy constructor" << std::endl;

  std::copy(m.data.get(), m.data.get() + this->height * this->width, this->data.get());
}

Matrix& Matrix::operator=(const Matrix& m)
{
    std::cout << "Copy assignment operator" << std::endl;

    if (this == &m)
    {
      return *this;
    }

    if (this->height != m.height && this->width != m.width)
    {
        this->data.reset();
        this->data = std::unique_ptr<double[]>(new double[m.height * m.width]);
        this->height = m.height;
        this->width = m.width;
    }
    std::copy(m.data.get(), m.data.get() + this->height * this->width, this->data.get());

    return *this;
}

Matrix::Matrix(Matrix&& m) : height(m.height), width(m.width), data(std::move(m.data)) 
{
  std::cout << "Move constructor" << std::endl;
}

Matrix& Matrix::operator=(Matrix&& m)
{
    std::cout << "Move assignment operator" << std::endl;

    if (this == &m)
    {
      return *this;
    }

    this->data = std::move(m.data);
    this->height = m.height;
    this->width = m.width;

    m.height = 0;
    m.width = 0;

    return *this;
}

Matrix Matrix::operator-() const
{
  Matrix new_matrix(this->height, this->width);

  for (std::size_t i = 1; i <= this->height; i++)
  {
    for (std::size_t j = 1; j <= this->width; j++)
    {
      new_matrix(i, j) = -(*this)(i, j);
    }
  }

  return new_matrix;
}

double Matrix::operator()(std::size_t row, std::size_t column) const 
{
  if (this->data.get() == nullptr) 
  {
    throw "No data";
  }

  return this->data[(row - 1) * this->width + (column - 1)];
}

double &Matrix::operator()(std::size_t row, std::size_t column) 
{
  return this->data[(row - 1) * this->width + (column - 1)];
}

std::ostream &operator<<(std::ostream &os, const Matrix &m) 
{
  for (size_t i = 1; i <= m.height; i++) 
  {
    for (size_t j = 1; j <= m.width; j++) 
    {
      os << m(i, j);

      if (j != m.width) 
      {
        os << " ";
      }
    }
    os << std::endl;
  }
  return os;
}

Matrix::~Matrix() 
{ 
    this->data.reset(); 
}