#ifndef RANDOM_HPP
#define RANDOM_HPP

/*
Exercise 1. Threads and mutex.
Program random.cpp fills an array with random values then replaces each element x with f(x).
Finally it computes sum of elements in the array.
When generateArray is called in parallel by two threads the output changes. The order of elements
can change but the sum should remain the same. Correct the algorithm to avoid data races.
Make the number of threads used a parameter of the algorithm.
Change computeSum function so that it could be run in parallel by several threads.
*/

#include <algorithm>
#include <future>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <vector>

template <int N> struct Array
{
    int data[N]{};

    int threads_count = 0;

    std::mutex mutex;
    std::mutex rand_mutex;

    int f(int x)
    {
        int y = x % 11;
        return (y * y + 1);
    }

    void generateArray(int threads = 1)
    {
        if (threads <= 0)
        {
            throw std::invalid_argument("Number of threads must be positive");
        }

        int interval = (N % threads == 0) ? (N / threads) : (N / threads) + 1;

        mutex.lock();

        if (threads == threads_count)
        {
            threads_count = 0;
        }

        int start = threads_count * interval;
        int end = std::min((threads_count + 1) * interval, N);
        threads_count++;

        if (threads == threads_count)
        {
            threads_count = 0;
        }

        mutex.unlock();

        int i = start;
        while (i < end)
        {
            rand_mutex.lock();
            data[i++] = rand();
            rand_mutex.unlock();
        }
        i = start;
        while (i < end)
        {
            data[i] = f(data[i]);
            i++;
        }
    }

    long long int computeSum(int threads = 1)
    {
        if (threads <= 0)
        {
            throw std::invalid_argument("Number of threads must be positive");
        }

        int interval = (N % threads == 0) ? (N / threads) : (N / threads) + 1;

        std::vector<std::future<int>> futures;
        for (int i = 0; i < N; i += interval)
        {
            futures.push_back(std::async(
                std::launch::async,
                [&](int start, int end) {
                    int interval_sum = 0;
                    for (int j = start; j < end; j++)
                    {
                        interval_sum += data[j];
                    }
                    return interval_sum;
                },
                i, std::min(i + interval, N)));
        }

        return std::accumulate(futures.begin(), futures.end(), 0,
                               [](int sum, std::future<int> &f) { return sum + f.get(); });
    }
};

#endif // RANDOM_HPP