#include "vector_operators.hpp"

int main()
{
    using V = Vector<10>;
    V v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    V x(v);
    V y{4, 4, 2, 5, 3, 2, 3, 4, 2, 1};

    std::cout << "Lazy operations :\n";
    // It does not create temporary Vectors
    // It computes resulting vector coordinate by coordinate
    // (evaluating whole expression)
    V z = v + x + 3 * y - 2 * x;
    std::cout << z << std::endl;

    // Computes only one coordinate of Vector
    int e = (z + x + y)[2];
    std::cout << " e = " << e << std::endl;
    return 0;
}
/**
 Init list constr
 Copy constr
 Init list constr
Lazy operations :
 Default constr
12, 12, 6, 15, 9, 6, 9, 12, 6, 3,
e = 11
 */