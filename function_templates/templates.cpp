#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <vector>

template <typename T> T sqr(T x)
{
    return x * x;
}

template <> std::string sqr(std::string s)
{
    return s + s;
}

template <unsigned N> int mod(int a, int b)
{
    return (a + b) % N;
}

template <> int mod<0>(int a, int b)
{
    return (a + b);
}

template <typename Container> void print(const Container &v)
{
    std::string separator = "";
    for (auto &elem : v)
    {
        std::cout << separator << elem;
        separator = " ";
    }
    std::cout << std::endl;
}

template <typename C, typename F> C applyFun(const C &c, F f)
{
    C result(c.size());
    std::transform(c.begin(), c.end(), result.begin(), f);
    return result;
}

template <typename T, T (*f)(T), unsigned N> void process(T array[])
{
    std::transform(array, array + N, array, f);
}