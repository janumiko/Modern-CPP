#include "matrix.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    using DMatrix = Matrix<double, 3, 4>;
    DMatrix m({{1, 2, 3, 4}, // constructor from
               {5, 6, 7, 8}, // initialization_list
               {9, 10, 11, 12}});
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Matrix m\n";
    for (auto elem : m)
    {
        std::cout << std::setw(6) << elem << " ";
    }

    std::cout << std::endl;
    auto sum = std::accumulate(m.begin(), m.end(), 0.0);
    std::cout << "sum of all elements = " << sum << std::endl;

    auto prod = std::inner_product(m.row_begin(1), m.row_end(1), m.row_begin(2), 0.0);
    std::cout << "inner product of 1st and 2nd row = " << prod << std::endl;

    for (DMatrix::column_iterator it = m.column_begin(3); it != m.column_end(3); ++it)
    {
        std::cout << std::setw(6) << *it << " ";
    }

    std::cout << std::endl;

    auto prod2 = std::inner_product(m.column_begin(1), m.column_end(1), m.column_begin(3), 0.0);
    std::cout << "inner product of 1st and 3rd column = " << prod2 << std::endl;

    Matrix<std::vector<int>, 2, 3> mv = {{{1, 2}, {1, 4, 5}, {1, 2, 3, 4}}, {{1}, {1, 4, 2, 3}, {5, 4}}};
    std::cout << "sizes of vectors in second row" << std::endl;
    for (auto it = mv.row_begin(2); it != mv.row_end(2); ++it)
    {
        std::cout << it->size() << std::endl;
    }

    const auto mconst = m;
    std::cout << " mconst = ";
    for (auto x : m)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}

/**
* Expected output:
Matrix m
  1.00   2.00   3.00   4.00   5.00   6.00   7.00   8.00   9.00  10.00  11.00  12.00
sum of all elements = 78.00
inner product of 1st and 2nd row = 70.00
  3.00   7.00  11.00
inner product of 1st and 3rd column = 137.00
sizes of vectors in second row
1
4
2
mconst = 1.00   2.00   3.00   4.00   5.00   6.00   7.00   8.00   9.00  10.00  11.00  12.00

 */