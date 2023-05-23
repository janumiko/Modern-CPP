#include <iostream>
#include <list>
#include <vector>

#include "median.hpp"

int main()
{
    std::list<int> a{3, 2, 5, 1, 4};
    std::cout << median(a) << std::endl; // 3
    std::vector<int> v{3, 1, 4, 2};
    std::cout << median(v) << std::endl; // 2.5
}