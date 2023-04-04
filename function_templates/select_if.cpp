#include <algorithm>
#include <deque>
#include <iostream>
#include <list>
#include <vector>

bool biggerThan5(int x)
{
    return x > 5;
}

/// TODO
template <template <typename, typename> class OutContainer, template <typename, typename> class InContainer, typename T,
          typename Alloc, typename Predicate>
OutContainer<T, Alloc> selectIf(const InContainer<T, Alloc> &c, Predicate p)
{
    OutContainer<T, Alloc> out(std::count_if(c.begin(), c.end(), p));
    std::copy_if(c.begin(), c.end(), out.begin(), p);
    return out;
}

int main()
{
    auto print = [](auto v) {
        for (auto x : v)
            std::cout << x << " ";
        std::cout << std::endl;
    };

    std::vector<int> v = {1, 2, 13, 4, 5, 54};
    std::list<int> result = selectIf<std::list>(v, biggerThan5);
    print(result); //  13 54

    auto result2 = selectIf<std::deque>(v, [](int x) -> bool { return x % 2; });
    print(result2); //  1 13 5

    auto result3 = selectIf<std::vector>(result2, biggerThan5);
    print(result3); //  13
    return 0;
}
