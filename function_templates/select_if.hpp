#ifndef SELECT_IF_HPP
#define SELECT_IF_HPP

#include <algorithm>
#include <deque>
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

#endif // SELECT_IF_HPP
