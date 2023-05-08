#ifndef RANGE_HPP
#define RANGE_HPP

#include <iostream>

template <typename T> class Range
{
  private:
    T _start;
    T _end;
    T _step;

  public:
    Range(T start, T end, T step = 1) : _start(start), _end(end), _step(step)
    {
    }

    Range(T end) : _start(0), _end(end), _step(1)
    {
    }

    class Iterator
    {
      private:
        T _end;
        T _step;
        T _current_index;

      public:
        Iterator(T current_index, T end, T step) : _end(end), _step(step), _current_index(current_index)
        {
        }

        T operator*()
        {
            return _current_index;
        }

        Iterator operator++(int)
        {
            Iterator iter{*this};
            operator++();
            return iter;
        }

        Iterator &operator++()
        {
            _current_index = std::min(_current_index + _step, _end);
            return *this;
        }

        friend inline bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs._current_index == rhs._current_index;
        }

        friend inline bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            return !operator==(lhs, rhs);
        }

        friend inline bool operator<(const Iterator &lhs, const Iterator &rhs)
        {
            return lhs._current_index < rhs._current_index;
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

    Iterator begin()
    {
        return Iterator(_start, _end, _step);
    }

    Iterator end()
    {
        return Iterator(_end, _end, _step);
    }
};

template <typename T> Range<T> make_range(T &&end)
{
    return Range<T>(std::forward<T>(end));
}

template <typename T> Range<T> make_range(T &&start, T &&end, T &&step = 1)
{
    return Range<T>(std::forward<T>(start), std::forward<T>(end), std::forward<T>(step));
}

#endif // RANGE_HPP
