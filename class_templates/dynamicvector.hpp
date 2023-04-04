#ifndef DYNAMICVECTOR_HPP
#define DYNAMICVECTOR_HPP

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>

#ifndef VECTOR_EXCEPTIONS
#define VECTOR_EXCEPTIONS

class VectorException : public std::runtime_error
{
  public:
    VectorException() : runtime_error("")
    {
    }
    VectorException(std::string s) : runtime_error(s)
    {
    }
};
#endif

template <typename T, std::size_t N> class Vector;

template <typename T, std::size_t N> std::ostream &operator<<(std::ostream &, const Vector<T, N> &);

template <typename T> class Vector<T, 0>
{
  private:
    std::unique_ptr<T[]> _data{nullptr};
    std::size_t _size{0};

    Vector(T v, std::size_t size) : _data(new T[size]), _size(size)
    {
        std::fill(_data.get(), _data.get() + size, v);
    }

  public:
    typedef T value_type;

    Vector() : _data(nullptr), _size(0)
    {
    }

    Vector(std::size_t size) : _data(new T[size]), _size(size)
    {
    }

    Vector(const Vector<T, 0> &vec) : _data(new T[vec.size()]), _size(vec.size())
    {
        std::copy(vec._data.get(), vec._data.get() + vec.size(), _data.get());
    }

    Vector(std::initializer_list<T> args) : _data(new T[args.size()]), _size(args.size())
    {
        std::copy(args.begin(), args.end(), _data.get());
    }

    const T &operator[](std::size_t index) const
    {
        return _data[index];
    }

    T &operator[](std::size_t index)
    {
        return _data[index];
    }

    std::size_t size() const
    {
        return _size;
    }

    void resize(std::size_t size)
    {
        auto new_data = std::make_unique<T[]>(size);
        std::copy(_data.get(), _data.get() + std::min(size, _size), new_data.get());

        _data = std::move(new_data);
        _size = size;
    }

    Vector<T, 0> operator+(const Vector<T, 0> &vec) const
    {
        if (_size != vec.size())
        {
            throw VectorException("Incompatible sizes in Vector::operator+");
        }

        Vector<T, 0> res(*this);

        for (std::size_t i = 0; i < _size; i++)
        {
            res[i] += vec[i];
        }
        return res;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector<T, 0> &vec)
    {
        out << "[";

        std::string separator = "";
        for (std::size_t i = 0; i < vec.size(); i++)
        {
            out << separator << vec[i];
            separator = " ";
        }

        out << "]";
        return out;
    }

    template <std::size_t N> explicit operator Vector<T, N>() const
    {
        Vector<T, N> vec;
        for (std::size_t i = 0; i < std::min(N, _size); i++)
        {
            vec[i] = _data[i];
        }

        return vec;
    }

    template <std::size_t N> Vector(Vector<T, N> &vec) : _data(new T[vec.size()]), _size(vec.size())
    {
        for (std::size_t i = 0; i < vec.size(); i++)
        {
            _data[i] = vec[i];
        }
    }

    template <std::size_t N> Vector<T, N> operator+(const Vector<T, N> &vec) const
    {
        if (_size != vec.size())
        {
            throw VectorException("Incompatible sizes in Vector::operator+");
        }

        Vector<T, N> res(*this);

        for (std::size_t i = 0; i < _size; i++)
        {
            res[i] += vec[i];
        }
        return res;
    }
};

#endif // DYNAMICVECTOR_HPP