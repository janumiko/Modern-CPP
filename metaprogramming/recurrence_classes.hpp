#ifndef RECURRENCE_CLASSES_HPP
#define RECURRENCE_CLASSES_HPP

using const_ll = const long long int;

template <int N, int P> struct Power
{
    constexpr static const_ll value = N * Power<N, P - 1>::value;
};

template <int N> struct Power<N, 0>
{
    constexpr static const_ll value = 1;
};

template <int N, int k> struct Binomial
{
    constexpr static const_ll value = Binomial<N - 1, k - 1>::value + Binomial<N - 1, k>::value;
};

template <int N> struct Binomial<N, 0>
{
    constexpr static const_ll value = 1;
};

template <int N> struct Binomial<N, N>
{
    constexpr static const_ll value = 1;
};

#endif // RECURRENCE_CLASSES_HPP