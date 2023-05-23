#include <iostream>
#include <vector>

#include "sfinae.hpp"

int main()
{
    /*
    Implement template classes that use SFINAE to detect during compilation:
    • hasSize<T> - if given type T has method size()
    • hasValueType<T> - if given type T has member type value_type
    */

    std::cout << hasSize<int>::value << std::endl;                   // false
    std::cout << hasSize<std::vector<int>>::value << std::endl;      // true
    std::cout << hasValueType<int>::value << std::endl;              // false
    std::cout << hasValueType<std::vector<int>>::value << std::endl; // true

    std::vector<int> v{1, 2, 3, 4, 5};
    std::cout << v1::getSize(5) << std::endl; // 4
    std::cout << v1::getSize(v) << std::endl; // 20
    std::cout << v2::getSize(5) << std::endl; // 4
    std::cout << v2::getSize(v) << std::endl; // 20
    return 0;
}