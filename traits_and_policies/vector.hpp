#ifndef LAB8_VECTOR_H
#define LAB8_VECTOR_H

#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "vector_policies.hpp"
#include "vector_traits.hpp"

template <typename T, size_t N, typename Policy = SafePolicy> class Vector
{
    T data[N];

  public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef T *pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef typename VectorTraits<T>::scalar_type scalar_type;
    typedef typename VectorTraits<T>::return_type return_type;
    typedef typename VectorTraits<T>::parameter_type parameter_type;
    typedef typename VectorTraits<T>::Type type;

    Vector()
    {
        Policy::init(data, N);
    };
    Vector(const Vector &v) = default;
    Vector &operator=(const Vector &m) = default;

    Vector(const std::initializer_list<T> &list)
    {
        Policy::init(data, list, N);
    }

    size_type size() const
    {
        return N;
    }

    return_type get(size_type index) const
    {
        Policy::check(index, N);
        return data[index];
    }

    void set(size_type index, parameter_type value)
    {
        Policy::check(index, N);
        data[index] = value;
    }

    friend Vector operator*(scalar_type x, const Vector &v)
    {
        Vector result;
        for (int i = 0; i < v.size(); ++i)
        {
            result.set(i, VectorTraits<T>::multiplicate(x, v.get(i)));
        }
        return result;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector &v)
    {
        for (int i = 0; i < v.size(); ++i)
        {
            out << v.get(i) << " ";
        }
        return out;
    }

    friend std::istream &operator>>(std::istream &in, Vector &v)
    {
        Vector::value_type value;
        for (int i = 0; i < v.size(); ++i)
        {
            in >> value;
            if (in)
                v.set(i, value);
        }
        return in;
    }
};

#endif // LAB8_VECTOR_H