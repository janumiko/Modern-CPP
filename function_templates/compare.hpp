#ifndef COMPARE_HPP
#define COMPARE_HPP

struct Rational
{
    int nominator = 0, denominator = 1;
    friend bool operator<(const Rational &a, const Rational &b)
    {
        return a.nominator * b.denominator < b.nominator * a.denominator;
    }
};

template <typename T> int compare(T a, T b)
{
    if (a < b)
    {
        return 1;
    }

    if (b < a)
    {
        return -1;
    }

    return 0;
}

template <typename T> int compare(T *a, T *b)
{
    if (*a < *b)
    {
        return 1;
    }

    if (*b < *a)
    {
        return -1;
    }

    return 0;
}

template <> int compare(const char *a, const char *b)
{
    int v = strcmp(a, b);

    if (v > 0)
    {
        return 1;
    }

    if (v < 0)
    {
        return -1;
    }

    return 0;
}

#endif // COMPARE_HPP
