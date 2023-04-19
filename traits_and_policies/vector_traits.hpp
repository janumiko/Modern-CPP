#ifndef VECTOR_TRAITS_HPP
#define VECTOR_TRAITS_HPP

#include <string>

template <typename T> struct VectorTraits
{
    typedef T Type;
    typedef Type scalar_type;
    typedef const Type &return_type;
    typedef const Type &parameter_type;

    static Type multiplicate(scalar_type scalar, parameter_type param)
    {
        return scalar * param;
    }
};

template <> struct VectorTraits<int>
{
    typedef int Type;
    typedef Type scalar_type;
    typedef Type return_type;
    typedef Type parameter_type;

    static Type multiplicate(scalar_type scalar, parameter_type param)
    {
        return scalar * param;
    }
};

template <> struct VectorTraits<double>
{
    typedef double Type;
    typedef Type scalar_type;
    typedef Type return_type;
    typedef Type parameter_type;

    static Type multiplicate(scalar_type scalar, parameter_type param)
    {
        return scalar * param;
    }
};

template <> struct VectorTraits<std::string>
{
    typedef std::string Type;
    typedef int scalar_type;
    typedef const Type &return_type;
    typedef const Type &parameter_type;

    static Type multiplicate(scalar_type scalar, parameter_type param)
    {
        Type result;
        result.reserve(param.size() * scalar);

        for (int i = 0; i < scalar; ++i)
        {
            result += param;
        }

        return result;
    }
};

#endif // VECTOR_TRAITS_HPP