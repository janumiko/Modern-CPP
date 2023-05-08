#ifndef FILTER_HPP
#define FILTER_HPP

#include <algorithm>
#include <utility>

template <typename Container, typename Predicate> class Filter
{
  private:
    Container _container;
    const Predicate &_predicate;

  public:
    Filter(Container &&container, const Predicate &predicate)
        : _container(std::forward<Container>(container)), _predicate(predicate)
    {
    }

    class Iterator
    {
      private:
        Container _container;
        using iterator = typename std::remove_reference_t<Container>::iterator;

        const Predicate &_predicate;
        iterator _iterator;

        using value_type = decltype(*_iterator);

      public:
        Iterator(iterator iter, const Predicate &p, Container &c) : _iterator{iter}, _predicate{p}, _container{c}
        {
        }

        Iterator &operator++()
        {
            ++_iterator;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp{*this};
            operator++();
            return tmp;
        }

        value_type &operator*()
        {
            while (!_predicate(*_iterator) && _iterator != std::end(_container))
            {
                operator++();
            }
            return *_iterator;
        }

        friend inline bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs._iterator == rhs._iterator;
        }

        friend inline bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            return !operator==(lhs, rhs);
        }

        friend inline bool operator<(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs._iterator < rhs._iterator;
        }

        friend inline bool operator>(const Iterator &lhs, const Iterator &rhs)
        {
            return operator<(rhs, lhs);
        }

        friend inline bool operator<=(const Iterator &lhs, const Iterator &rhs)
        {
            return !operator>(lhs, rhs);
        }

        friend inline bool operator>=(const Iterator &lhs, const Iterator &rhs)
        {
            return !operator<(lhs, rhs);
        }
    };

    using iterator = Iterator;

    iterator begin()
    {
        return Iterator(std::begin(_container), _predicate, _container);
    }

    iterator end()
    {
        return Iterator(std::end(_container), _predicate, _container);
    }
};

template <typename Container, typename Predicate> auto make_filter(Container &&c, Predicate p)
{
    return Filter<Container, Predicate>(std::forward<Container>(c), p);
}

#endif // FILTER_HPP
