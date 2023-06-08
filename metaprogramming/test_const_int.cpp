#include <array>
#include <cmath>
#include <iostream>

#include "const_int.hpp"

/**
 * Exercise 2a:
 * Implement function power that computes x^n
 * during compilation using recurrent formula
   x^2n = (x^n)^2
   x^2n+1 = (x^2n)*x
*/

/**
 *  Exercise 2b:
 * Implement function generate_triangle that during compilation
 * generates the Pascal trriangle of the given size N.
 * Pascal triangle
 * https://en.wikipedia.org/wiki/Pascal%27s_triangle
 *
 */

constinit double fiveToPowerFour = power(5, 4);

template <auto N> consteval PascalTriangle<N> generatePascalTriangle()
{
    return PascalTriangle<N>();
}

constexpr size_t n = 10;
constexpr auto triangle = generatePascalTriangle<n>();

int main()
{
    static_assert(triangle(0, 0) == 1);
    static_assert(triangle(5, 3) == 10);
    static_assert(triangle(9, 4) == 126);
}
