#include <iostream>
#include <vector>

#include "concepts.hpp"

template <typename T> class A
{
  protected:
    T x;

  public:
    A(T x = T()) : x(x)
    {
    }

    void print() const
    {
        std::cout << "[" << x << "]";
    }
};

template <typename T> class B : public A<T>
{
  public:
    using A<T>::A;

    friend std::ostream &operator<<(std::ostream &out, const B &b)
    {
        return (out << "#" << b.x << "#");
    }

    friend B operator+(const B &a, const B &b)
    {
        return B(a.x + b.x);
    }
};

int main()
{
    std::vector v{1, 2, 4, 5};
    print(v);
    A<int> a{5};
    print(a);
    B<double> b{3.14};
    print(b);
    print(2.7);
    std::vector<A<int>> va{4, 5, 7, 9};
    std::vector<B<int>> vb{4, 5, 7, 9};
    print(va);
    print(vb);
    print(sum(v));
    print(sum(vb));
    return 0;
}
/**
* Expected output
0 : 1
1 : 2
2 : 4
3 : 5
-------
[5]
#3.14#
2.7
0 : [4]
1 : [5]
2 : [7]
3 : [9]
-------
0 : #4#
1 : #5#
2 : #7#
3 : #9#
-------
12
#25#
*/
