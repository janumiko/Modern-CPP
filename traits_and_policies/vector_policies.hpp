#ifndef VECTOR_POLICIES_HPP
#define VECTOR_POLICIES_HPP

#include <iostream>

struct BasePolicy
{
    template <typename T> static void init(T *data, int N){};
    template <typename T> static void init(T *data, const std::initializer_list<T> &list, int N){};
    static void check(int index, int N){};
};

struct SafePolicy : public BasePolicy
{
    template <typename T> static void init(T *data, int N)
    {
        const T &result = T();
        std::fill(data, data + N, result);
    }

    template <typename T> static void init(T *data, const std::initializer_list<T> &list, int N)
    {
        if (list.size() > N)
        {
            std::cout << "Initalizer list is too long." << std::endl;
        }

        std::copy(list.begin(), std::min(list.begin() + N, list.end()), data);
    }

    static void check(int index, int N)
    {
        if (index < 0 || index >= N)
        {
            std::cout << "Index out of range" << std::endl;
        }
    }
};

struct FastPolicy : public BasePolicy
{
    template <typename T> static void init(T &data, int N)
    {
    }

    template <typename T> static void init(T *data, const std::initializer_list<T> &list, int N)
    {
        std::copy(list.begin(), std::min(list.begin() + N, list.end()), data);
    }
};

struct InitFastPolicy : public BasePolicy
{
    template <typename T> static void init(T *data, int N)
    {
        const T &result = T();
        std::fill(data, data + N, result);
    }

    template <typename T> static void init(T *data, const std::initializer_list<T> &list, int N)
    {
        std::copy(list.begin(), std::min(list.begin() + N, list.end()), data);
    }
};

#endif // VECTOR_POLICIES_HPP