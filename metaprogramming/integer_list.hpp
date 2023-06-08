#ifndef INTEGER_LIST_HPP
#define INTEGER_LIST_HPP

#include <iostream>

template <int Head, int... Tail> class IntegerList
{
  public:
    constexpr static int max()
    {
        if constexpr (sizeof...(Tail) == 0)
        {
            return Head;
        }
        else
        {
            return std::max(Head, IntegerList<Tail...>::max());
        }
    }

    constexpr static int get(int index)
    {
        if (index == 0)
        {
            return Head;
        }
        else if constexpr (sizeof...(Tail) == 0)
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            return IntegerList<Tail...>::get(index - 1);
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const IntegerList &list)
    {
        os << Head << " ";
        ((os << Tail << " "), ...);
        return os;
    }
};

template <int Index, typename L> struct getInt;

template <int Index, int... L> struct getInt<Index, IntegerList<L...>>
{
    constexpr static const int value = IntegerList<L...>::get(Index);
};

template <typename L, typename R> struct Join;

template <int... L, int... R> struct Join<IntegerList<L...>, IntegerList<R...>>
{
    using type = IntegerList<L..., R...>;
};

template <typename L> struct IsSorted;

template <int... L> struct IsSorted<IntegerList<L...>>
{
    constexpr static const bool value = (... < L);
};

template <typename L> struct Max;

template <int... L> struct Max<IntegerList<L...>>
{
    constexpr static const int value = std::max({L...});
};

#endif // INTEGER_LIST_HPP