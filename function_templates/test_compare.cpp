#include <cstring>
#include <iostream>

#include "compare.hpp"

int main()
{
    int a = 1, b = -6;
    float y = 1.0 + 1e20 - 1e20, x = 1.0;
    std::cout << compare(a, b) << " " << compare(b, a) << " " << compare(a, a) << std::endl;
    std::cout << compare(x, y) << " " << compare(y, x) << " " << compare(x, x) << std::endl;
    std::cout << compare(&a, &b) << " " << compare(&b, &a) << " " << compare(&a, &a) << std::endl;
    std::cout << compare(&x, &y) << " " << compare(&y, &x) << " " << compare(&x, &x) << std::endl;
    std::cout << compare("Alpha", "Alfa") << std::endl;

    return 0;
}
