#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

#include <concepts>
#include <iostream>
#include <numeric>
#include <vector>

template <typename T>
concept Container = requires(T t)
{
    typename T::value_type;
    {
        t.begin()
        } -> std::same_as<typename T::iterator>;
    {
        t.end()
        } -> std::same_as<typename T::iterator>;
};

template <typename T>
concept HasPrintFunction = requires(T t)
{
    {t.print()};
};

template <typename T>
concept HasPrintOperator = requires(T t)
{
    {std::cout << t};
};

template <typename T> void print(const T &c)
{
    if constexpr (Container<T>)
    {
        for (const auto &e : c)
        {
            print(e);
        }
    }
    else if constexpr (HasPrintOperator<T>)
    {
        std::cout << c << std::endl;
    }
    else if constexpr (HasPrintFunction<T>)
    {
        c.print();
    }
    else
    {
        std::cout << c << std::endl;
    }
}

template <typename T> auto sum(const T &c)
{
    if constexpr (Container<T>)
    {
        return std::reduce(c.begin(), c.end());
    }
    else
    {
        return c;
    }
}

#endif // CONCEPTS_HPP