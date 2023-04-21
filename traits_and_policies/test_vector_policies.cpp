#include "vector.hpp"
#include <iostream>

int main()
{
    int value = 5;
    { /// sets coordinates to zero and checks indices
        using Vect = Vector<double, 3, SafePolicy>;
        Vect a{};
        a.set(1, -1);                       // OK
        std::cout << a << std::endl;        // 0 -1 0
        a.set(-1, 1.);                      // Exception
        std::cout << a.get(3) << std::endl; // Exception
        Vect b{1, 2, 3, 4};                 // Exception
    }
    { /// does not initialize by default and does not check indices
        using Vect = Vector<double, 3, FastPolicy>;
        Vect a{};
        a.set(1, -1);                       // OK
        std::cout << a << std::endl;        // Unspecified (random values on first and third coordinate)
        a.set(-1, 1.);                      // Unspecified
        std::cout << value << std::endl;    // value possibly changed by the previous line
        std::cout << a.get(3) << std::endl; // Unspecified
        Vect b{1, 2, 3, 4};                 // OK: it makes copy of only first three values
    }
    { /// initializes to zero by default but does not check indices
        using Vect = Vector<double, 3, InitFastPolicy>;
        Vect a{};
        a.set(1, -1);                       // OK
        std::cout << a << std::endl;        // OK: 0 -1 0
        a.set(-1, 1.);                      // Unspecified
        std::cout << value << std::endl;    // value possibly changed by the previous line
        std::cout << a.get(3) << std::endl; // Unspecified
        Vect b{1, 2, 3, 4};                 // OK: it makes copy of only first three values
    }
    return 0;
}
