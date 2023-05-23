#ifndef MEDIAN_HPP
#define MEDIAN_HPP

template <typename Container> double median(Container set, std::random_access_iterator_tag)
{
    std::size_t size = set.size();

    if (size == 0)
    {
        return 0;
    }

    std::sort(set.begin(), set.end());

    if (size % 2 == 0)
    {
        return (set[size / 2 - 1] + set[size / 2]) / 2.0;
    }
    else
    {
        return set[size / 2];
    }
}

template <typename Container> double median(Container set, std::forward_iterator_tag)
{
    std::size_t size = set.size();

    if (size == 0)
    {
        return 0;
    }

    std::vector<typename Container::value_type> v(set.begin(), set.end());
    std::sort(v.begin(), v.end());

    if (size % 2 == 0)
    {
        return (v[size / 2 - 1] + v[size / 2]) / 2.0;
    }
    else
    {
        return v[size / 2];
    }
}

template <typename Container> double median(Container set)
{
    return median(set, typename std::iterator_traits<typename Container::iterator>::iterator_category());
}

#endif // MEDIAN_HPP