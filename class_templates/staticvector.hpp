#ifndef STATICVECTOR_HPP
#define STATICVECTOR_HPP

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>

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

template <typename T, std::size_t N> class Vector
{
  private:
    T data[N];

    Vector(T v) : data()
    {
        std::fill(data, data + N, v);
    }

  public:
    typedef T value_type;

    Vector() : data()
    {
    }

    Vector(std::initializer_list<T> args) : data()
    {
        std::copy(args.begin(), args.end(), data);
    }

    const T &operator[](std::size_t index) const
    {
        return data[index];
    }

    T &operator[](std::size_t index)
    {
        return data[index];
    }

    std::size_t size() const
    {
        return N;
    }

    template <std::size_t M> Vector<T, N> operator+(const Vector<T, M> &vec) const
    {
        if (vec.size() != this->size())
        {
            throw VectorException("Incompatible sizes in Vector::operator+");
        }

        Vector<T, N> res(*this);

        for (std::size_t i = 0; i < vec.size(); i++)
        {
            res[i] += vec[i];
        }
        return res;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector<T, N> &vec)
    {
        out << "[";

        std::string separator = "";
        for (const auto &v : vec.data)
        {
            out << separator << v;
            separator = " ";
        }

        out << "]";
        return out;
    }

    template <typename S, std::size_t M> operator Vector<S, M>() const
    {
        Vector<S, M> vec;
        for (std::size_t i = 0; i < std::min(M, N); i++)
        {
            vec[i] = (S)data[i];
        }
        return vec;
    }
};

#endif // STATICVECTOR_HPP