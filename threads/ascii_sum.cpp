#include <algorithm>
#include <fstream>
#include <future>
#include <iostream>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

void ascii_sum(std::promise<int> *p, const std::string &filename)
{
    std::fstream file(filename, std::ios::in);

    int sum = 0;

    std::string s;
    while (file >> s)
    {
        sum = std::accumulate(s.begin(), s.end(), sum, [](int a, char b) { return a + (int)b; });
    }

    file.close();

    p->set_value(sum);
}

int main(int argc, char *argv[])
{
    std::vector<std::future<int>> futures;
    std::vector<std::promise<int>> promises;
    std::vector<std::thread> threads;
    futures.reserve(argc - 1);
    promises.reserve(argc - 1);
    threads.reserve(argc - 1);

    for (int i = 1; i < argc; ++i)
    {
        promises.emplace_back();
        futures.push_back(promises.at(i - 1).get_future());
        threads.emplace_back(ascii_sum, &promises.at(i - 1), argv[i]);
    }

    for (int j = 0; j < argc - 1; ++j)
    {
        if (threads.at(j).joinable())
        {
            threads.at(j).join();
        }
    }

    std::vector<std::pair<std::string, int>> results;

    for (int k = 0; k < futures.size(); ++k)
    {
        results.emplace_back(std::make_pair(argv[k + 1], futures.at(k).get()));
    }

    std::sort(
        results.begin(), results.end(),
        [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) { return a.second < b.second; });

    for (auto &r : results)
    {
        std::cout << r.first << " " << r.second << std::endl;
    }

    // print all equal pairs
    for (int i = 0; i < results.size() - 1; i++)
    {
        if (results.at(i).second == results.at(i + 1).second)
        {
            std::cout << results.at(i).first << " is equal to " << results.at(i + 1).first << std::endl;
        }
    }

    return 0;
}