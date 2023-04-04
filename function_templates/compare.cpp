#include <cstring>
#include <iostream>

using namespace std;

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

int main()
{
    int a = 1, b = -6;
    float y = 1.0 + 1e20 - 1e20, x = 1.0;
    cout << compare(a, b) << " " << compare(b, a) << " " << compare(a, a) << endl;
    cout << compare(x, y) << " " << compare(y, x) << " " << compare(x, x) << endl;
    cout << compare(&a, &b) << " " << compare(&b, &a) << " " << compare(&a, &a) << endl;
    cout << compare(&x, &y) << " " << compare(&y, &x) << " " << compare(&x, &x) << endl;
    cout << compare("Alpha", "Alfa") << endl;

    return 0;
}
