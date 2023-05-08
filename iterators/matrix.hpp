#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <algorithm>
#include <iomanip>
#include <iostream>

template <typename T, std::size_t N, std::size_t M> class Matrix
{
  private:
    T _data[N * M];

  public:
    constexpr std::size_t numberOfRows() const
    {
        return N;
    }

    constexpr std::size_t numberOfColumns() const
    {
        return M;
    }

    Matrix(int nrows = N, int ncols = M)
    {
        std::fill_n(_data, N * M, T{});
    }

    Matrix(const std::initializer_list<std::initializer_list<T>> &list)
    {
        T *p = _data;
        for (const auto &row : list)
        {
            T *p2 = std::copy(row.begin(), row.end(), p);
            std::fill(p2, p += M, T{});
        }
    }

    Matrix(const Matrix &m)
    {
        std::copy_n(m._data, N * M, _data);
    }

    Matrix &operator=(const Matrix &m)
    {
        if (&m != this)
        {
            std::copy_n(m._data, N * M, _data);
        }
        return *this;
    }

    const T &operator()(int i, int j) const
    {
        return _data[(i - 1) * M + j - 1];
    }

    T &operator()(int i, int j)
    {
        return _data[(i - 1) * M + j - 1];
    }

    friend Matrix operator+(const Matrix &a, const Matrix &b)
    {
        Matrix r;
        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= M; ++j)
            {
                r(i, j) = a(i, j) + b(i, j);
            }
        }
        return r;
    }

    class Iterator
    {
      private:
        T *_iterator;
        std::size_t _step;

      public:
        Iterator(T *iterator, std::size_t _step = 1) : _iterator{iterator}, _step{_step}
        {
        }

        Iterator &operator++()
        {
            _iterator += _step;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp{*this};
            operator++();
            return tmp;
        }

        T &operator*()
        {
            return *_iterator;
        }

        const T &operator*() const
        {
            return *_iterator;
        }

        T *operator->()
        {
            return _iterator;
        }

        const T *operator->() const
        {
            return _iterator;
        }

        friend inline bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs._iterator == rhs._iterator;
        }

        friend inline bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            return !operator==(lhs, rhs);
        }

        friend inline bool operator<(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs._iterator < rhs._iterator;
        }

        friend inline bool operator>(const Iterator &lhs, const Iterator &rhs)
        {
            return operator<(rhs, lhs);
        }

        friend inline bool operator<=(const Iterator &lhs, const Iterator &rhs)
        {
            return !operator>(lhs, rhs);
        }

        friend inline bool operator>=(const Iterator &lhs, const Iterator &rhs)
        {
            return !operator<(lhs, rhs);
        }
    };

    using iterator = Iterator;
    using row_iterator = Iterator;
    using column_iterator = Iterator;
    using const_iterator = const Iterator;

    iterator begin()
    {
        return Iterator(_data);
    }

    iterator end()
    {
        return Iterator(_data + N * M);
    }

    row_iterator row_begin(std::size_t n)
    {
        return Iterator(_data + (n - 1) * M);
    }

    row_iterator row_end(std::size_t n)
    {
        return Iterator(_data + n * M);
    }

    column_iterator column_begin(std::size_t n)
    {
        return Iterator(_data + (n - 1), M);
    }

    column_iterator column_end(std::size_t n)
    {
        return Iterator(_data + N * M + (n - 1));
    }
};

template <typename T, std::size_t N, std::size_t M> void printMatrix(const Matrix<T, N, M> &m, int width = 10)
{
    for (int i = 1; i <= m.numberOfRows(); ++i)
    {
        for (int j = 1; j <= m.numberOfColumns(); ++j)
        {
            if (j != 1)
            {
                std::cout << " ";
            }
            std::cout << std::setw(width) << m(i, j);
        }
        std::cout << std::endl;
    }
}

#endif // MATRIX_HPP