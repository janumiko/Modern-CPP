#include "multi_vector.hpp"
#include <iostream>
#include <vector>

int main()
{
    MultiVector<int, std::string, double> m;
    m.push_back(5);
    m.push_back(std::string("text"));
    m.push_back(7);
    m.push_back(1.2);
    m.print(); // [ 5 7 ] [ text ] [ 1.2 ]
    std::cout << std::endl;
    auto v = std::move(m);
    for (auto x : {1, 2, 3})
    {
        v.push_back(x + 10);
        v.push_back(std::to_string(x));
        v.push_back(x / 10.0);
    }
    m.print(); // [ ] [ ] [ ]   but can be undefined
    std::cout << std::endl;
    v.print(); // [ 5 7 11 12 13 ] [ text 1 2 3 ] [ 1.2 0.1 0.2 0.3 ]
    std::cout << std::endl;
    MultiVector<int, int, double, int> w;
    w.push_back(1);
    w.push_back(2.0);
    w.print(); // [ 1 ] [ ] [ 2 ] [ ]
    std::cout << std::endl;
}
/*
[ 5 7 ] [ text ] [ 1.2 ]
[ ] [ ] [ ]
[ 5 7 11 12 13 ] [ text 1 2 3 ] [ 1.2 0.1 0.2 0.3 ]
[ 1 ] [ ] [ 2 ] [ ]
 */