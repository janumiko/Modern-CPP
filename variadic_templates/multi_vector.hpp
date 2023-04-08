#ifndef MULTI_VECTOR_HPP
#define MULTI_VECTOR_HPP

#include <iostream>
#include <vector>

template <typename... Types> class MultiVector
{
  public:
    void print(){};
};

template <typename Head, typename... Tail> class MultiVector<Head, Tail...>
{
  private:
    std::vector<Head> head;
    MultiVector<Tail...> tail;

  public:
    void push_back(Head v)
    {
        head.push_back(v);
    }

    template <typename T> void push_back(T v)
    {
        tail.push_back(v);
    }

    void print()
    {
        std::cout << "[";
        std::string separator = "";
        for (const auto &elem : head)
        {
            std::cout << separator << elem;
            separator = " ";
        }
        std::cout << "] ";
        tail.print();
    }
};

#endif