#include <iomanip>
#include <iostream>
#include <type_traits>

#include "integer_list.hpp"

int main()
{
    using listA = IntegerList<5, -1, 5, 2, 1>;
    using listB = IntegerList<1, 4, 6, 9>;
    std::cout << "List A : " << listA() << std::endl;
    std::cout << "List B : " << listB() << std::endl;

    std::cout << "A[1] = " << getInt<1, listA>::value << std::endl;
    std::cout << "B[3] = " << listB::get(3) << std::endl;
    static_assert(getInt<1, listA>::value == -1);
    static_assert(listB::get(3) == 9);
    static_assert(listB::get(1) == 4);

    std::cout << std::boolalpha;
    std::cout << "Is A sorted? " << IsSorted<listA>::value << std::endl;
    std::cout << "Is B sorted? " << IsSorted<listB>::value << std::endl;

    using listC = Join<listA, listB>::type;

    std::cout << "List C : " << listC() << std::endl;
    std::cout << Max<listC>::value << std::endl;
    std::cout << listC::max() << std::endl;
    static_assert(listC::max() == 9);
    static_assert(listA::max() == 5);
}

/*
Exercise 3. IntegerList
Implement
• variadic class template IntegerList, that can “store” integer values as template arguments,
• template class getInt<index, IntegerList> that turns element with a given index for the
IntegerList,
• template class Join<IntegerList1, IntegerList2> that joins two IntegerLists,
• template class IsSorted<IntegerList> that checks if arguments of IntegerList are sorted,
• template class Max<IntegerList> that finds maximal element in given list of integers.
In class IntegerList implement static constexpr functions:
• get(int index) that returns with a given index for the IntegerList,
• max() that finds maximal element in the IntegerList
*/