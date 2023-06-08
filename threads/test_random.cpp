#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>
#include <iostream>
#include <iterator>
#include <numeric>
#include <thread>
#include <utility>
#include <vector>

#include "random.hpp"

const int array_size = 1000;

int main()
{
    srand(2019);
    using A = Array<array_size>;
    A array;

    int number_of_threads;

    std::cout << "Enter number of threads: ";
    std::cin >> number_of_threads;

    std::vector<std::thread> threads;
    for (int i = 0; i < number_of_threads; i++)
    {
        threads.emplace_back(&A::generateArray, &array, number_of_threads);
    }

    for (int i = 0; i < number_of_threads; i++)
    {
        if (threads.at(i).joinable())
        {
            threads.at(i).join();
        }
    }

    std::string separator = "";
    for (int i = 0; i < 40; i++)
    {
        std::cout << separator << array.data[i];
        separator = ", ";
    }
    std::cout << std::endl;

    std::cout << "Single threaded sum = " << std::accumulate(array.data, array.data + array_size, 0) << std::endl;

    long long sum = array.computeSum(number_of_threads);
    std::cout << "Multithreaded sum = " << sum << std::endl;
}
