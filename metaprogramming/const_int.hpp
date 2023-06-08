#ifndef CONST_INT.HPP
#define CONST_INT .HPP

#include <array>
#include <cmath>

consteval auto power(auto x, int n)
{
    if (n == 0)
    {
        return 1;
    }

    if (n % 2 == 0)
    {
        return power(x, n / 2) * power(x, n / 2);
    }
    else
    {
        return power(x, n - 1) * x;
    }
}

template <size_t N> class PascalTriangle
{
  private:
    std::array<std::array<int, N>, N> data{};

  public:
    consteval PascalTriangle()
    {
        for (int i = 0; i < N; i++)
        {
            data[i][0] = 1;
            data[i][i] = 1;
        }

        for (int i = 2; i < N; i++)
        {
            for (int j = 1; j < i; j++)
            {
                data[i][j] = data[i - 1][j - 1] + data[i - 1][j];
            }
        }
    }

    consteval int operator()(size_t n, size_t m) const
    {
        return data[n][m];
    }
};

#endif // CONST_INT.HPP