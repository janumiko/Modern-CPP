#ifndef SFINAE_HPP
#define SFINAE_HPP

#include <iostream>

template <typename T, typename = void> struct hasSize : std::false_type
{
};

template <typename T> struct hasSize<T, std::void_t<decltype(std::declval<T>().size())>> : std::true_type
{
};

template <typename T, typename = void> struct hasValueType : std::false_type
{
};

template <typename T> struct hasValueType<T, std::void_t<typename T::value_type>> : std::true_type
{
};

namespace v1
{

template <typename T>
constexpr typename std::enable_if<hasSize<T>::value && hasValueType<T>::value, std::size_t>::type getSize(const T &x)
{
    return x.size() * sizeof(typename T::value_type);
}

template <typename T>
constexpr typename std::enable_if<!(hasSize<T>::value && hasValueType<T>::value), std::size_t>::type getSize(const T &x)
{
    return sizeof(x);
}

} // namespace v1

namespace v2
{

template <typename T> std::size_t getSize(const T &x)
{
    if constexpr (hasSize<T>::value && hasValueType<T>::value)
    {
        return x.size() * sizeof(typename T::value_type);
    }
    else
    {
        return sizeof(T);
    }
}

} // namespace v2

#endif // SFINAE_HPP