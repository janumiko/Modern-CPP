#ifndef FOLD_HPP
#define FOLD_HPP

#include <cmath>
#include <functional>

template <typename... Args> double average(Args... args)
{
    return (0.0 + ... + args) / sizeof...(args);
}

template <typename Func, typename... Args> int computeSum(Func f, Args... args)
{
    return (0 + ... + f(args));
}

template <typename Container, typename... Args> void insert(Container &container, Args... args)
{
    (..., container.insert(container.end(), args));
}

#endif